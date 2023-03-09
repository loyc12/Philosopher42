/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/09 11:55:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//creates the philosophers' threads
void	start_threads(t_meta *m)
{
	t_philo	*p;
	int		i;

	printf("> Init_threads started\n"); //DEBUG

	m->state = MSTATE_RUNING;
	m->start_time = get_time();

	i = -1;
	while (++i < m->philo_count)
	{
		p = m->philos[i];
		if (pthread_create(m->p_threads[i], NULL, philosopher, m->philos[i]))
		{
			throw_error(ERR_THREAD);
			m->state = MSTATE_ERROR;
			return ;
		}
		//usleep(THREAD_W); //wait time in us between thread starts //					no waiting?
	}

	printf("> Init_threads completed\n"); //DEBUG
}

//initializes the fork structs
void	init_forks(t_meta *m)
{
	int	i;

	printf("> Init_forks started\n"); //DEBUG

	i = -1;
	m->forks = calloc(m->philo_count, sizeof(t_fork *));
	while (++i < m->philo_count)
	{
		m->forks[i] = calloc(1, sizeof(t_fork));
		m->forks[i]->fork_id = i;
		if (pthread_mutex_init(&m->forks[i]->f_mutex, NULL))
		{
			throw_error(ERR_MUTEX);
			m->state = MSTATE_ERROR;
			return ;
		}
	}

	printf("> Init_forks completed\n"); //DEBUG
}

//initializes the philosopher structs
void	init_philos(t_meta *m)
{
	t_philo	*p;
	int		i;

	printf("> Init_philos started\n"); //DEBUG

	i = -1;
	m->philos = calloc(m->philo_count, sizeof(t_philo *));
	m->p_threads = calloc(m->philo_count, sizeof(pthread_t *));
	while (++i < m->philo_count)
	{
		m->philos[i] = calloc(1, sizeof(t_philo));
		m->p_threads[i] = calloc(m->philo_count, sizeof(pthread_t));
		p = m->philos[i];
		p->m = m;
		p->philo_id = i + 1; //+1 cause no 0
		p->right_fork = m->forks[i];
		p->left_fork = m->forks[(i + 1) % m->philo_count];
	}

	printf("> Init_philos completed\n"); //DEBUG
}

/*
	2p : c = 2e : t = 2e - (e + s) : t = max((e - s), 0)	: d ~ e
	3p : c = 3e : t = 3e - (e + s) : t = max((2e - s), 0)	: d ~ 2e

	if (p_n == 1)					//solo case
		t = t_death + 10d
	else if							//even case
		t = max((e - s), 0) + d
	else							//uneven case
		t = max((2e - s), 0) + 2d
*/

void	set_times(t_meta *m, char **av)
{
	m->philo_count = ft_atoi(av[1]);
	m->time_death = ft_atoi(av[2]);
	m->time_eat = ft_atoi(av[3]);
	m->time_sleep = ft_atoi(av[4]);

	if (av[5])
		m->meal_limit = ft_atoi(av[5]);

	if (m->philo_count == 1)
		m->time_think = 2 * m->time_death; //solo case
	else if (m->philo_count % 2 == 0)
		m->time_think = m->time_eat - m->time_sleep; //even case
	else
		m->time_think = (2 * m->time_eat) - m->time_sleep; //uneven case

	if (m->time_think < 0)
		m->time_think = 0;

	printf("> Time_think value : %i\n", m->time_think); //DEBUG
}

//initialises g_meta and its sub structs/things
int	init_meta(t_meta *m, char **av)
{
	printf("> Init_meta started\n"); //DEBUG

	set_times(m, av);

	if (m->philo_count > 0 && m->philo_count <= PHILO_M
		&& m->time_death >= 0 && m->time_eat >= 0
		&& m->time_sleep >= 0 && (!av[5] || m->meal_limit >= 0))
	{
		init_forks(m);
		init_philos(m);
		if (m->state > MSTATE_ERROR)
			return (EXIT_SUCCESS);
		free_all(m);
	}
	else if (m->philo_count > PHILO_M)
		throw_error(ERR_P_CNT);
	else if (m->philo_count == 0)
		throw_error(ERR_P_NONE);

	return (EXIT_FAILURE);
}
