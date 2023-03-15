/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/15 17:10:25 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//makes the philo eat while checking for death. returns 1 if dead, 0 if successful
int	eat_n_check(t_philo *p)
{
	long long	time; //in ns

	if (check_stop_flags(p))
		return (1);

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_EAT);

	time = get_time();
	while (time_dif(time) < p->m->time_eat)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(SLEEP_T);
	}
	return (0);
}

//makes the philo sleep while checking for death. returns 1 if dead, 0 if successful
int	sleep_n_check(t_philo *p)
{
	long long	time; //in ns

	if (check_stop_flags(p))
		return (1);

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_SLEEP);

	time = get_time();
	while (time_dif(time) < p->m->time_sleep)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(SLEEP_T);
	}
	return (0);
}

//makes the philo think while checking for death. returns 1 if dead, 0 if successful
int	think_n_check(t_philo *p)
{
	long long	time; //in ns

	if (check_stop_flags(p))
		return (1);

	print_action(time_dif(p->m->start_time), p->philo_id, ACT_THINK);

	time = get_time();
	while (time_dif(time) < p->m->time_think)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(SLEEP_T);
	}
	return (0);
}

//picks up the forks, make the philo eat, and then puts them back
int	eat_w_forks(t_philo *p)
{
	if (check_stop_flags(p))
		return (1);

	//picks the left fork and locks its mutex
	pthread_mutex_lock(&(p->left_fork->f_mutex));
	if (check_stop_flags(p))
	{
		pthread_mutex_unlock(&(p->left_fork->f_mutex));
		return (1);
	}
	print_action(time_dif(p->m->start_time), p->philo_id, ACT_TAKE);

	//picks the right fork and locks its mutex
	pthread_mutex_lock(&(p->right_fork->f_mutex));
	if (check_stop_flags(p))
	{
		pthread_mutex_unlock(&(p->left_fork->f_mutex));
		pthread_mutex_unlock(&(p->right_fork->f_mutex));
		return (1);
	}
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
}
