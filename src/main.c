/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/09 15:24:28 by llord            ###   ########.fr       */
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

	//print_action(time_dif(p->m), p->philo_id, ACT_BORN); //DEBU

	if ((p->philo_id % 2) == 1) //makes uneven wait
	{
		delay = 1000 * (p->m->time_eat); //make it wait an extra amount per philosopher?					TODO
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
			m->state = MSTATE_ERROR;
			return ;
		}
	}

	//printf("> Init_threads completed\n"); //DEBUG
}

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
	usleep(1000);
	while (1)
	{
		if (check_death(m))
			break ;
		if (m->meal_limit >= 0 && check_meal_count(m))
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&(m->m_mutex));
	m->state = MSTATE_ENDING;
	pthread_mutex_unlock(&(m->m_mutex));
}

//main logic for philosopher
int	run_philo(t_meta *m)
{
	//printf("> Run_philo started\n"); //DEBUG

	start_threads(m);

	if (m->state > MSTATE_ERROR) //only waits for death if the threading worked
		make_checks(m);

	wait_threads(m);

	//printf("> Run_philo completed\n"); //DEBUG

	if (m->state <= MSTATE_ERROR) //only fail if the threading failed
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

void	print_philos(t_meta *m)
{
	t_philo *p;
	int	i;

	i = -1;
	while (++i < m->philo_count)
	{
		p = m->philos[i];
		printf("\n Philo #%i\n", p->philo_id);
		printf(" Death : %i\n", p->state);
		printf(" Meals : %i\n", p->meal_count);
	}
}

//USE FT_CALLOC!!!!!!
//entrypoint function
int	main(int ac, char **av)
{
	int		exit_status;
	t_meta	*m;

	if (ac != 5 && ac != 6) //checks for a proper argcount
		return (throw_error(ERR_A_CNT));

	m = calloc(1, sizeof(t_meta));
	if (init_meta(m, av)) //initilizes t_meta and all its sub structs/things
		return (throw_error(ERR_INIT));

	//printf("> Init_meta completed\n"); //DEBUG

	exit_status = run_philo(m); //runs the main logic loop

	print_philos(m);

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