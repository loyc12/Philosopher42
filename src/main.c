/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/06 15:07:43 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//threaded function (READ ABOUT THREADS)
void	*philosopher(void *void_philo)
{
	t_meta	*m;
	t_philo	*p;
	int		i;

	return (NULL);
}

//loops until a philosopher dies
void	wait_death(t_meta *m)
{
	int	i;

	i = -1;
	while (m->state == MSTATE_RUNING)
	{
		m->state = MSTATE_ENDING; //checks for death here
	}
}

//main logic loop
int	main_loop(t_meta *m)
{
	int	i;

	m->state = MSTATE_RUNING;
	m->start_time = get_time();

	init_threads(m);

	wait_death(m);

	kill_threads(m);

	return (EXIT_SUCCESS);
}

//entrypoint function
int	main(int ac, char **av)
{
	t_meta	*m;
	int		exit_status;

	if (ac != 5 && ac != 6) //checks for a proper argcount
		return (throw_error(ERR_ARG));

	if (init_meta(&m, av)) //initilizes t_meta and all its sub structs/things
		return (throw_error(ERR_INIT));

	exit_status = main_loop(m); //runs the main logic loop

	free_all(m);

	return (exit_status);
}
