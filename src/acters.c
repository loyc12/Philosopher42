/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/09 15:14:03 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop_flags(t_philo *p)
{
	pthread_mutex_lock(&(p->m->m_mutex));
	if (p->m->state == MSTATE_ENDING) //checks for ending flag during sleep
	{
		pthread_mutex_unlock(&(p->m->m_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(p->m->m_mutex));
	if (time_dif(p->last_meal) > p->m->time_death) //checks for death during sleep
	{
		print_action(time_dif(p->m->start_time), p->philo_id, ACT_DIE);

		pthread_mutex_lock(&(p->p_mutex));
		p->state = PSTATE_DEAD;
		pthread_mutex_unlock(&(p->p_mutex));

		return (1);
	}
	return (0);
}

//makes the philo eat while checking for death. returns 1 if dead, 0 if successful
int	eat_n_check(t_philo *p)
{
	long long	time; //in ns

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_EAT);

	time = get_time();
	while (time_dif(time) < p->m->time_eat)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(1000);
	}
	return (0);
}

//makes the philo think while checking for death. returns 1 if dead, 0 if successful
int	think_n_check(t_philo *p)
{
	long long	time; //in ns

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_THINK);

	time = get_time();
	while (time_dif(time) < p->m->time_think)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(1000);
	}
	return (0);
}

//makes the philo sleep while checking for death. returns 1 if dead, 0 if successful
int	sleep_n_check(t_philo *p)
{
	long long	time; //in ns

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_SLEEP);

	time = get_time();
	while (time_dif(time) < p->m->time_sleep)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(1000);
	}
	return (0);
}

int	eat_w_forks(t_philo *p)
{
	if (check_stop_flags(p))
		return (1);

	//picks both forks and locks their mutex
	pthread_mutex_lock(&(p->left_fork->f_mutex));
	print_action(time_dif(p->m->start_time), p->philo_id, ACT_TAKE);

	pthread_mutex_lock(&(p->right_fork->f_mutex));
	print_action(time_dif(p->m->start_time), p->philo_id, ACT_TAKE);

	//eats
	p->last_meal = get_time();
	if (eat_n_check(p))
	{
		pthread_mutex_unlock(&(p->left_fork->f_mutex));
		pthread_mutex_unlock(&(p->right_fork->f_mutex));
		return (1);
	}

	//places back both forks and unlocks their mutex
	pthread_mutex_unlock(&(p->left_fork->f_mutex));
	pthread_mutex_unlock(&(p->right_fork->f_mutex));

	//update the philo's mealcount
	pthread_mutex_lock(&(p->p_mutex));
	p->meal_count++;
	pthread_mutex_unlock(&(p->p_mutex));

	return (0);
}

void	live(t_philo *p)
{
	while (1)
	{
		if (eat_w_forks(p))
			break ;
		if (sleep_n_check(p))
			break ;
		if (think_n_check(p))
			break ;
	}

	p->m->state = MSTATE_ENDING;
}
