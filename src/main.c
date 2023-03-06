/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/06 14:23:53 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//writes a given error message (from DEFINE)
int	throw_error(char *error)
{
	int	len;

	len = 0;
	while (error[len])
	len++;
	write(2, &error, len);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

//prints a given action (from DEFINE)
void	print_action(int time, int philo_id, char *action)
{
	printf("%i : %i %s", time, philo_id, action);
}

//converts a string into an interger
int	ft_atoi(const char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;

	while ('0' <= str[i] && str[i] <= '9')
		number == (number *= 10) + (str[i++] - '0');
	if (!str[i])
		return (number);
	throw_error(ERR_NUM);
	return (-1);
}

//initializes the fork structs
void	init_forks(t_meta *m)
{
	int	i;

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
		}
	}
}

//initializes the philosopher structs
void	init_philos(t_meta *m)
{
	int	i;

	i = -1;
	m->philos = calloc(m->philo_count, sizeof(t_philo *));
	while (++i < m->philo_count)
	{
		m->philos[i] = calloc(1, sizeof(t_philo));
		m->philos[i]->philo_id = i;
		m->philos[i]->m = m;
		m->philos[i]->right_fork = m->forks[i];
		m->philos[i]->left_fork = m->forks[(i + 1) % m->philo_count];
		//pthread_create(&m->philos[i], NULL, philosopher, &m->philo_threads[i]);
	}
}

//initialises g_meta
int	init_meta(t_meta *m, char **av)
{
	m = calloc(1, sizeof(t_meta));

	m->philo_count = ft_atoi(av[1]);
	m->time_death = ft_atoi(av[2]);
	m->time_eat = ft_atoi(av[3]);
	m->time_sleep = ft_atoi(av[4]);
	if (av[5])
		m->meal_limit = ft_atoi(av[5]);
	if (m->philo_count >= 0 && m->time_death >= 0 && m->time_eat >= 0
		&& m->time_sleep >= 0 && (!av[5] || m->meal_limit >= 0))
	{
		init_forks(m);
		//init_mutex if needed?
		init_philos(m);
		if (m->state > MSTATE_ERROR)
			return (EXIT_SUCCESS);
	}
	free_null(ADRS m); //replace me with free_all
	return (EXIT_FAILURE);
}

//main philosopher logic
int	start_loop(t_meta *m)
{
	int	i;

	m->start_time = timestamp();
	m->state = MSTATE_RUNING;
	i = -1;
	while (++i < m->philo_count)
	{
		//start threads for each philo
	}
	while (m->state == MSTATE_RUNING)
	{
		//check for death
	}
	i = -1;
	while (++i < m->philo_count)
	{
		//join back every thread
	}
	return (EXIT_SUCCESS);
}

//entrypoint function
int	main(int ac, char **av)
{
	t_meta	*m;
	int		exit_status;

	if (ac != 5 && ac != 6)
		return (throw_error(ERR_ARG));

	if (init_meta(&m, av))
		return (throw_error(ERR_INIT));

	exit_status = start_loop(m);

	free_null(ADRS m); //replace me with free_all

	return (exit_status);
}
