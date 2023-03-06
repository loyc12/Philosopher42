/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:00:02 by llord             #+#    #+#             */
/*   Updated: 2023/03/06 15:18:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_all(t_meta *m)
{
	int	i;

	kill_mutex(m);
	i = -1;
	while (++i < m->philo_count)
	{
		free_null(ADRS m->philos[i]);
		free_null(ADRS m->forks[i]);
	}
	free_null(ADRS m);
}

//takes a pointer's adress and frees whatever is there, setting it to NULL after
void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

//removes the philosophers' threads
void	kill_threads(t_meta *m)
{
	int		i;

	i = -1;
	while (++i < m->philo_count)
	{
		pthread_join(m->p_threads[i], NULL);
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
	}
}