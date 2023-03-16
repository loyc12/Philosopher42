/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/16 13:23:37 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//makes the philo eat while checking for death. returns 1 if dead
int	eat_n_check(t_philo *p)
{
	if (check_stop_flags(p))
		return (1);
	print_action(p->m, get_time_dif(p->m->start_time), p->philo_id, ACT_EAT);
	if (smart_sleep(p, p->m->time_eat))
		return (1);
	return (0);
}

//makes the philo sleep while checking for death. returns 1 if dead
int	sleep_n_check(t_philo *p)
{
	if (check_stop_flags(p))
		return (1);
	print_action(p->m, get_time_dif(p->m->start_time), p->philo_id, ACT_SLEEP);
	if (smart_sleep(p, p->m->time_sleep))
		return (1);
	return (0);
}

//makes the philo think while checking for death. returns 1 if dead
int	think_n_check(t_philo *p)
{
	if (check_stop_flags(p))
		return (1);
	print_action(p->m, get_time_dif(p->m->start_time), p->philo_id, ACT_THINK);
	if (smart_sleep(p, p->m->time_think))
		return (1);
	return (0);
}

//picks up the forks, make the philo eat, and then puts them back
int	eat_w_forks(t_philo *p)
{
	pthread_mutex_lock(&(p->left_fork->f_mutex));
	if (check_stop_flags(p))
		return (pthread_mutex_unlock(&(p->left_fork->f_mutex)), 1);
	print_action(get_time_dif(p->m->start_time), p->philo_id, ACT_TAKE);
	pthread_mutex_lock(&(p->right_fork->f_mutex));
	if (check_stop_flags(p))
	{
		pthread_mutex_unlock(&(p->left_fork->f_mutex));
		return (pthread_mutex_unlock(&(p->right_fork->f_mutex)), 1);
	}
	print_action(p->m, get_time_dif(p->m->start_time), p->philo_id, ACT_TAKE);
	p->last_meal = (int)get_time_dif(0);
	if (eat_n_check(p))
	{
		pthread_mutex_unlock(&(p->left_fork->f_mutex));
		return (pthread_mutex_unlock(&(p->right_fork->f_mutex)), 1);
	}
	pthread_mutex_unlock(&(p->left_fork->f_mutex));
	pthread_mutex_unlock(&(p->right_fork->f_mutex));
	pthread_mutex_lock(&(p->p_mutex));
	p->meal_count++;
	return (pthread_mutex_unlock(&(p->p_mutex)), 0);
}

void	live(t_philo *p)
{
	while (1)
	{
		if (check_stop_flags(p))
			break ;
		if (eat_w_forks(p))
			break ;
		if (sleep_n_check(p))
			break ;
		if (think_n_check(p))
			break ;
	}
}
