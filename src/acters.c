/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/09 11:56:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_w_forks(t_philo *p)
{
	//picks both forks and locks mutex
	pthread_mutex_lock(&(p->left_fork->f_mutex));
	pthread_mutex_lock(&(p->right_fork->f_mutex));
	//print_action(time_dif(p->m), p->philo_id, ACT_TAKE);
	//print_action(time_dif(p->m), p->philo_id, ACT_TAKE);

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_EAT);

	p->last_meal = get_time();
	usleep(1000 * p->m->time_eat);
	p->meal_count++;
	p->last_meal = get_time();

	//places back both forks and unlocks mutex
	pthread_mutex_unlock(&(p->left_fork->f_mutex));
	pthread_mutex_unlock(&(p->right_fork->f_mutex));
}

//ameks the philo sleep while checking for death. returns 1 if dead, 0 if successful
int	sleep_n_check(t_philo *p)
{
	int32_t	time_i; //in ms

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_SLEEP);

	time_i = -1;
	while (++time_i < p->m->time_sleep)
	{
		if (p->m->state == MSTATE_ENDING)
			return (0);
		if (time_dif(p->last_meal) > p->m->time_death) //checks for death during sleep
			return (1);
		usleep(1000);
	}
	return (0);
}

int	think_n_check(t_philo *p)
{
	int	time_i; //in ms

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_THINK);

	time_i = -1;
	while (++time_i < p->m->time_think)
	{
		if (p->m->state == MSTATE_ENDING)
			return (0);
		if (time_dif(p->last_meal) > p->m->time_death) //checks for death during sleep
			return (1);
		usleep(1000);
	}
	return (0);
}

void	live(t_philo *p)
{
	while (1)
	{
		eat_w_forks(p);
		if (sleep_n_check(p))
			break ;
		if (think_n_check(p))
			break ;
	}
	p->m->state = MSTATE_ENDING;
	print_action(time_dif(p->m->start_time), p->philo_id, ACT_DIE);
}
