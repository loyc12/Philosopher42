/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/08 11:37:30 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//threaded function (READ ABOUT THREADS)
void	*philosopher(void *_p)
{
	t_philo	*p;
	long	delay;

	p = (t_philo *)_p;

	//print_action(time_dif(p->m), p->philo_id, ACT_BORN); //DEBU

	if ((p->philo_id % 2) == 1) //makes uneven wait
	{
		delay = 1000 * (p->m->time_eat); //make it wait an extra amount per philosopher?					TODO
		usleep(delay);
		if (p->philo_id == p->m->philo_count) //makes last one wait if uneven
			usleep(delay);
	}
	do_action(p, PSTATE_EATING);

	return (NULL);
}

//loops until a philosopher dies
void	wait_death(t_meta *m)
{
	int	i;

	i = -1;
	while (m->state == MSTATE_RUNING)
	{
		printf("> Skipping death check for now\n"); //DEBUG

		m->state = MSTATE_ENDING; //checks for death here
	}
}

//main logic loop
int	main_loop(t_meta *m)
{
	printf("> Main_loop started\n"); //DEBUG

	start_threads(m);

	if (m->state > MSTATE_ERROR) //only waits for death if the threading worked
		wait_death(m);

	kill_threads(m);

	if (m->state <= MSTATE_ERROR) //only fail if the threading failed
		return (EXIT_FAILURE);

	printf("> Main_loop completed\n"); //DEBUG

	return (EXIT_SUCCESS);
}

//USE FT_CALLOC!!!!!!
//entrypoint function
int	main(int ac, char **av)
{
	int		exit_status;
	t_meta	*m;

	m = NULL;
	if (ac != 5 && ac != 6) //checks for a proper argcount
		return (throw_error(ERR_A_CNT));

	m = calloc(1, sizeof(t_meta));
	if (init_meta(m, av)) //initilizes t_meta and all its sub structs/things
		return (throw_error(ERR_INIT));

	printf("> Init_meta completed\n"); //DEBUG

	exit_status = main_loop(m); //runs the main logic loop

	free_all(m);

	printf("> Program exited normally\n"); //DEBUG

	return (exit_status);
}

/*
thinking is the default state
start with uneven eating (safe last)

if the number is uneven, is a 3 cycle, else a two cycle

each "cycle" consist of eating, sleeping and then thinking, until they can eat again


*/