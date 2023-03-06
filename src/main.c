/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/06 15:57:31 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//threaded function (READ ABOUT THREADS)
void	*philosopher(void *_p)
{
	t_meta	*m;
	t_philo	*p;

	p = (t_philo *)_p;
	m = p->m;

	printf("launched thread #%i\n", p->philo_id); //DEBUG

	return (NULL);
}

//loops until a philosopher dies
void	wait_death(t_meta *m)
{
	int	i;

	i = -1;
	while (m->state == MSTATE_RUNING)
	{
		printf("skipping death check\n"); //DEBUG
		m->state = MSTATE_ENDING; //checks for death here
	}
}

//main logic loop
int	main_loop(t_meta *m)
{
	printf("main_loop start\n"); //DEBUG

	m->state = MSTATE_RUNING;
	m->start_time = get_time();

	init_threads(m);

	wait_death(m);

	kill_threads(m);

	printf("main_loop end\n"); //DEBUG

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
		return (throw_error(ERR_ARG));

	printf("valid args\n"); //DEBUG

	m = calloc(1, sizeof(t_meta));
	if (init_meta(m, av)) //initilizes t_meta and all its sub structs/things
		return (throw_error(ERR_INIT));

	printf("init_meta end\n"); //DEBUG

	exit_status = main_loop(m); //runs the main logic loop

	printf("normal exit\n"); //DEBUG

	free_all(m);

	return (exit_status);
}
