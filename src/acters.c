/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/08 11:41:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_w_forks(t_philo *p)
{
	//pick both forks if mutex allows
	//print_action(time_dif(p->m), p->philo_id, ACT_TAKE);
	//print_action(time_dif(p->m), p->philo_id, ACT_TAKE);

	print_action(time_dif(p->m), p->philo_id, ACT_EAT);

	p->last_meal = get_time();
	usleep(1000 * p->m->time_eat);
	p->last_meal = get_time();

	//place back both forks
}

//selects a given action and executes it (doesn't support born/pick)
void	do_action(t_philo *p, int new_state)
{
	if (p->state == new_state)
		printf("> "); //symbol for redundant state change

	p->state = new_state;

	if (new_state == PSTATE_DEAD)
	{
		print_action(time_dif(p->m), p->philo_id, ACT_DIE);
		p->m->state = MSTATE_ENDING; //protect with mutex???				TODO
	}
	else if (new_state == PSTATE_SLEEPING)
	{
		print_action(time_dif(p->m), p->philo_id, ACT_SLEEP);
		usleep(1000 * p->m->time_sleep);
	}
	else if (new_state == PSTATE_THINKING)
		print_action(time_dif(p->m), p->philo_id, ACT_THINK);
	else if (new_state == PSTATE_EATING)
		eat_w_forks(p);
	else
		throw_error(ERR_ACTION);

}
