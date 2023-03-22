/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/03/16 16:47:13 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//threaded function (READ ABOUT THREADS)
void	*philosopher(void *_p)
{
	t_philo	*p;
	int		delay;

	p = (t_philo *)_p;
	p->last_meal = p->m->start_time;
	pthread_mutex_lock(&(p->p_mutex));
	if (p->m->philo_count == 1)
	{
		pthread_mutex_unlock(&(p->p_mutex));
		if (think_n_check(p))
			return (NULL);
	}
	pthread_mutex_unlock(&(p->p_mutex));
	if ((p->philo_id % 2) == 1)
	{
		delay = 1000 * p->m->time_eat;
		usleep(delay);
		if (p->philo_id == p->m->philo_count)
			usleep(delay);
	}
	live(p);
	return (NULL);
}

//creates the philosophers' threads
void	start_threads(t_meta *m)
{
	t_philo	*p;
	int		i;

	m->state = MSTATE_RUNING;
	m->start_time = (int)get_time_dif(0);
	i = -1;
	while (++i < m->philo_count)
	{
		p = m->philos[i];
		if (pthread_create(m->threads[i], NULL, philosopher, m->philos[i]))
		{
			throw_error(ERR_THREAD);
			pthread_mutex_lock(&(m->m_mutex));
			m->state = MSTATE_ERROR;
			pthread_mutex_unlock(&(m->m_mutex));
			return ;
		}
		usleep(BORN_T);
	}
}

//main logic for philosopher
int	run_philo(t_meta *m)
{
	start_threads(m);
	pthread_mutex_lock(&(m->m_mutex));
	if (m->state > MSTATE_ERROR)
	{
		pthread_mutex_unlock(&(m->m_mutex));
		make_checks(m);
	}
	else
		pthread_mutex_unlock(&(m->m_mutex));
	wait_threads(m);
	if (m->state <= MSTATE_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//calloc
void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = count * size;
	if (i == 0)
		i++;
	ptr = malloc(i);
	if (!ptr)
		return (NULL);
	while (i > 0)
		ptr[i--] = 0;
	return ((void *)ptr);
}

//	WARNING :
//
//	each philosopher creates about 0.5ms of lag per cycle,
//	meaning 200 philo would only live if they have 100ms of extra time
//		for example; 200 300 100 100
//	where; (death_time ~= (philo_number * 0.5) + (2 * eat_time))
//
//	this does not affect uneven numbers of philosophers as much,
//	as the last philosopher can only eat when both other groups
//	(odd and even) are not eating, compensating for the lag
//		for example; 199 310 100 100
//	where; (death_time ~= (philo_number * 0.1) + (3 * eat_time))

//entrypoint function
int	main(int ac, char **av)
{
	int		exit_status;
	t_meta	*m;

	if (ac != 5 && ac != 6)
		return (throw_error(ERR_A_CNT));
	m = ft_calloc(1, sizeof(t_meta));
	if (init_meta(m, av))
		return (free_null(ADRS m), throw_error(ERR_INIT));
	exit_status = run_philo(m);
	free_all(m);
	return (exit_status);
}
