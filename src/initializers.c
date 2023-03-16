/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/16 13:09:21 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initializes the fork structs AND the t_meta mutex
void	init_forks(t_meta *m)
{
	int	i;

	//printf("> Init_forks started\n"); //DEBUG

	i = -1;
	m->forks = calloc(m->philo_count, sizeof(t_fork *));
	while (++i < m->philo_count)
	{
		m->forks[i] = calloc(1, sizeof(t_fork));
		m->forks[i]->fork_id = i;
	}

	//printf("> Init_forks completed\n"); //DEBUG
}

//initializes the philosopher structs
void	init_philos(t_meta *m)
{
	t_philo	*p;
	int		i;

	//printf("> Init_philos started\n"); //DEBUG

	i = -1;
	m->philos = calloc(m->philo_count, sizeof(t_philo *));
	m->threads = calloc(m->philo_count, sizeof(pthread_t *));
	while (++i < m->philo_count)
	{
		m->philos[i] = calloc(1, sizeof(t_philo));
		m->threads[i] = calloc(m->philo_count, sizeof(pthread_t));
		p = m->philos[i];
		p->m = m;
		p->philo_id = i + 1; //+1 cause no 0
		p->right_fork = m->forks[i];
		p->left_fork = m->forks[(i + 1) % m->philo_count];
	}

	//printf("> Init_philos completed\n"); //DEBUG
}

void	init_mutexes(t_meta *m)
{
	int	i;

	//printf("> Init_mutexes started\n"); //DEBUG

	i = -1;
	while (++i < m->philo_count)
	{
		if (pthread_mutex_init(&(m->philos[i]->p_mutex), NULL)
			|| pthread_mutex_init(&(m->forks[i]->f_mutex), NULL))
		{
			throw_error(ERR_MUTEX);
			m->state = MSTATE_ERROR;
			return ;
		}
	}
	if (pthread_mutex_init(&(m->m_mutex), NULL))
	{
		throw_error(ERR_MUTEX);
		m->state = MSTATE_ERROR;
		return ;
	}

	//printf("> Init_mutexes completed\n"); //DEBUG
}

//sets the constants for t_meta
void	set_consts(t_meta *m, char **av)
{
	m->philo_count = philo_atoi(av[1], 1);
	m->time_death = philo_atoi(av[2], 0);
	m->time_eat = philo_atoi(av[3], 0);
	m->time_sleep = philo_atoi(av[4], 0);

	if (av[5])
		m->meal_limit = philo_atoi(av[5], 0);
	else
		m->meal_limit = 0;

	find_time_think(m);
}

//initialises g_meta and its sub structs/things
int	init_meta(t_meta *m, char **av)
{
	//printf("> Init_meta started\n"); //DEBUG

	set_consts(m, av);

	if (m->philo_count > 0 && m->philo_count <= PHILO_M
		&& m->time_death > 0 && m->time_eat > 0
		&& m->time_sleep > 0 && (!av[5] || m->meal_limit > 0))
	{
		init_forks(m);
		init_philos(m);
		init_mutexes(m);
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
