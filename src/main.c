/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/03/15 17:05:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//threaded function (READ ABOUT THREADS)
void	*philosopher(void *_p)
{
	t_philo	*p;
	long	delay;

	p = (t_philo *)_p;

	p->last_meal = p->m->start_time;

	//print_action(time_dif(p->m), p->philo_id, ACT_BORN); //DEBUG

	if ((p->philo_id % 2) == 1) //makes uneven wait
	{
		delay = 1000 * p->m->time_eat;
		usleep(delay);
		if (p->philo_id == p->m->philo_count) //makes last one wait if uneven
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

	//printf("> Init_threads started\n"); //DEBUG

	m->state = MSTATE_RUNING;
	m->start_time = get_time();

	i = -1;
	while (++i < m->philo_count)
	{
		p = m->philos[i];
		if (pthread_create(m->p_threads[i], NULL, philosopher, m->philos[i]))
		{
			throw_error(ERR_THREAD);
			pthread_mutex_lock(&(m->m_mutex));
			m->state = MSTATE_ERROR;
			pthread_mutex_unlock(&(m->m_mutex));
			return ;
		}
		usleep(BORN_T);
	}

	//printf("> Init_threads completed\n"); //DEBUG
}

//main logic for philosopher
int	run_philo(t_meta *m)
{
	//printf("> Run_philo started\n"); //DEBUG

	start_threads(m);

	pthread_mutex_lock(&(m->m_mutex));
	if (m->state > MSTATE_ERROR) //only waits for death if the threading worked
	{
		pthread_mutex_unlock(&(m->m_mutex));
		make_checks(m);
	}
	pthread_mutex_unlock(&(m->m_mutex));

	wait_threads(m);

	//printf("> Run_philo completed\n"); //DEBUG

	if (m->state <= MSTATE_ERROR) //only fail if the threading failed
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

void	print_philos(t_meta *m) //DEBUG						REMOVE ME
{
	t_philo	*p;
	int		i;
	int		death_flag;

	i = -1;
	death_flag = 0;
	printf("\n");
	while (++i < m->philo_count)
	{
		p = m->philos[i];
		printf("#%i :", p->philo_id);
		printf(" Ate %i", p->meal_count);
		if (p->state == PSTATE_DEAD)
		{
			death_flag = 1;
			printf(" > !!! DEAD !!!");
		}
		printf("\n");
	}
	printf("\n");

	if (death_flag)
		printf("  Ran outta spagett, FOOL !!!\n\n");
	printf("  Settings : %i %i %i %i (%i)\n\n", m->philo_count, m->time_death, m->time_eat, m->time_sleep, m->time_think);
}

//USE FT_CALLOC!!!!!!
//entrypoint function
int	main(int ac, char **av)
{
	int		exit_status;
	t_meta	*m;

	if (ac != 5 && ac != 6) //checks for a proper argcount
		return (throw_error(ERR_A_CNT));

	m = calloc(1, sizeof(t_meta)); //CHAGNE TO FT_CALLOC !!!!!!
	if (init_meta(m, av)) //initilizes t_meta and all its sub structs/things
		return (throw_error(ERR_INIT));

	//printf("> Init_meta completed\n"); //DEBUG

	exit_status = run_philo(m); //runs the main logic loop

	if (m->state != MSTATE_ERROR)
		print_philos(m); //DEBUG

	free_all(m);

	//printf("> Program exited normally\n"); //DEBUG

	return (exit_status);
}

/*
thinking is the default state
start with uneven eating (safe last)

if the number is uneven, is a 3 cycle, else a two cycle

each "cycle" consist of eating, sleeping and then thinking, until they can eat again


*/