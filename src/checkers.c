/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:41:48 by llord             #+#    #+#             */
/*   Updated: 2023/03/16 12:44:30 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//locks every philo's p_mutex and checks their status. return 1 if one is dead
int	check_death(t_meta *m)
{
	int	i;

	i = -1;
	while (++i < m->philo_count)
	{
		pthread_mutex_lock(&(m->philos[i]->p_mutex));
		if (m->philos[i]->state == PSTATE_DEAD)
		{
			//printf("> Death detected\n"); //DEBUG
			pthread_mutex_unlock(&(m->philos[i]->p_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(m->philos[i]->p_mutex));
	}
	return (0);
}

//locks every philo's p_mutex and checks their meal count. return 0 if one is bellow limit
int	check_meal_count(t_meta *m)
{
	int	i;

	i = -1;
	while (++i < m->philo_count)
	{
		pthread_mutex_lock(&(m->philos[i]->p_mutex));
		if (m->philos[i]->meal_count < m->meal_limit)
		{
			pthread_mutex_unlock(&(m->philos[i]->p_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(m->philos[i]->p_mutex));
	}
	//printf("> Meal count reached\n"); //DEBUG
	return (1);
}

//loops until a philosopher dies or the meal limit is reached
void	make_checks(t_meta *m)
{
	usleep(SLEEP_T);
	while (1)
	{
		if (check_death(m))
			break ;
		if (m->meal_limit > 0 && check_meal_count(m))
			break ;
		usleep(SLEEP_T);
	}
	pthread_mutex_lock(&(m->m_mutex));
	m->state = MSTATE_ENDING;
	pthread_mutex_unlock(&(m->m_mutex));
}

//checks wheter a given philosopher has died or otherwise should stop
int	check_stop_flags(t_philo *p)
{
	pthread_mutex_lock(&(p->m->m_mutex));
	if (p->m->state == MSTATE_ENDING) //checks for ending flag during sleep
	{
		pthread_mutex_unlock(&(p->m->m_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(p->m->m_mutex));
	if ((int)get_time_dif(p->last_meal) >= p->m->time_death) //checks for death during sleep
	{
		print_action(p->m, get_time_dif(p->m->start_time), p->philo_id, ACT_DIE);

		pthread_mutex_lock(&(p->p_mutex));
		p->state = PSTATE_DEAD;
		pthread_mutex_unlock(&(p->p_mutex));

		return (1);
	}
	return (0);
}

/*
	2p	: c = 2e	: t = 2e - (e + s)	: t = max((e - s), 0)
	3p	: c = 3e	: t = 3e - (e + s)	: t = max((2e - s), 0)

	if (p_n == 1)					//solo case
		t = t_death + 10d
	else if							//even case
		t = max((e - s), 0) + d
	else							//uneven case
		t = max((2e - s), 0) + 2d
*/

//finds how long the philos ought to think for
void	find_time_think(t_meta *m)
{
	int	buffer_time;

	if (m->philo_count == 1) //solo case
	{
		m->time_think = 2 * m->time_death;
		buffer_time = 0;
	}
	else if (m->philo_count % 2 == 0) //even case
	{
		m->time_think = m->time_eat - m->time_sleep;
		buffer_time = (m->time_death - ((2 * m->time_eat) + m->time_sleep)) / 2;
	}
	else //uneven case
	{
		m->time_think = (2 * m->time_eat) - m->time_sleep;
		buffer_time = (m->time_death - ((3 * m->time_eat) + m->time_sleep)) / 2;
	}
	if (m->time_think < 0)
		m->time_think = 0;
	if (m->time_think < buffer_time)
		m->time_think = buffer_time;

	//printf("> Time_think value : %i\n", m->time_think); //DEBUG
}
