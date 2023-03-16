/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:00:02 by llord             #+#    #+#             */
/*   Updated: 2023/03/16 13:19:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_meta *m)
{
	int	i;

	kill_mutex(m);
	i = -1;
	while (++i < m->philo_count)
	{
		if (m->philos)
			free_null(ADRS m->philos[i]);
		if (m->forks)
			free_null(ADRS m->forks[i]);
		if (m->threads)
			free_null(ADRS m->threads[i]);
	}
	free_null(ADRS m->philos);
	free_null(ADRS m->forks);
	free_null(ADRS m->threads);
	free_null(ADRS m);
}

//takes a pointer's adress and frees whatever is there, setting it to NULL after
void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

//takes a array's adress and frees whatever is there, setting it to NULL after
void	free_array(void ***ptr)
{
	int	i;

	if (*ptr)
	{
		i = -1;
		while ((*ptr)[++i])
			free_null((void **) &((*ptr)[i]));
		free_null((void **)ptr);
	}
}

//waits until every thread is completed before continuing
void	wait_threads(t_meta *m)
{
	int		i;

	i = -1;
	while (++i < m->philo_count)
	{
		pthread_join(*m->threads[i], NULL);
	}
}

//removes the philosophers' threads
void	kill_mutex(t_meta *m)
{
	int		i;

	i = -1;
	while (++i < m->philo_count)
	{
		pthread_mutex_destroy(&(m->forks[i]->f_mutex));
		pthread_mutex_destroy(&(m->philos[i]->p_mutex));
	}
	pthread_mutex_destroy(&(m->m_mutex));
}
