/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/07 14:15:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//initializes the fork structs
void	init_forks(t_meta *m)
{
	int	i;

	printf("init_forks start\n"); //DEBUG

	i = -1;
	m->forks = calloc(m->philo_count, sizeof(t_fork *));
	while (++i < m->philo_count)
	{
		m->forks[i] = calloc(1, sizeof(t_fork));
		m->forks[i]->fork_id = i;
		if (pthread_mutex_init(&m->forks[i]->f_mutex, NULL))
		{
			throw_error(ERR_MUT);
			m->state = MSTATE_ERROR;
			return ;
		}
	}

	printf("init_forks end\n"); //DEBUG
}

//initializes the philosopher structs
void	init_philos(t_meta *m)
{
	t_philo	*p;
	int		i;

	printf("init_philos start\n"); //DEBUG

	i = -1;
	m->philos = calloc(m->philo_count, sizeof(t_philo *));
	m->p_threads = calloc(m->philo_count, sizeof(pthread_t *));
	while (++i < m->philo_count)
	{
		m->philos[i] = calloc(1, sizeof(t_philo));
		m->p_threads[i] = calloc(m->philo_count, sizeof(pthread_t));
		p = m->philos[i];
		p->m = m;
		p->philo_id = i;
		p->right_fork = m->forks[i];
		p->left_fork = m->forks[(i + 1) % m->philo_count];
	}

	printf("init_philos end\n"); //DEBUG
}

//creates the philosophers' threads
void	init_threads(t_meta *m)
{
	t_philo	*p;
	int		i;

	printf("init_threads start\n"); //DEBUG

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
		usleep(THREAD_W); //wait time in us between thread starts
	}

	printf("init_threads end\n"); //DEBUG
}

//initialises g_meta and its sub structs/things
int	init_meta(t_meta *m, char **av)
{
	printf("init_meta start\n"); //DEBUG

	m->philo_count = ft_atoi(av[1]);
	m->time_death = ft_atoi(av[2]);
	m->time_eat = ft_atoi(av[3]);
	m->time_sleep = ft_atoi(av[4]);
	if (m->philo_count > PHILO_M)
	{
		m->start_time = MSTATE_ERROR;
		throw_error(ERR_P_NB);
	}
	if (av[5])
		m->meal_limit = ft_atoi(av[5]);
	if (m->philo_count >= 0 && m->time_death >= 0 && m->time_eat >= 0
		&& m->time_sleep >= 0 && (!av[5] || m->meal_limit >= 0))
	{
		init_forks(m);
		init_philos(m);
		if (m->state > MSTATE_ERROR)
			return (EXIT_SUCCESS);
	}

	return (EXIT_FAILURE);
}
