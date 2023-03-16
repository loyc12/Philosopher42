/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/16 12:36:21 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//writes a given error message (defined in .h)
int	throw_error(char *error)
{
	int	len;

	len = 0;
	while (error[len])
		len++;
	write(2, error, len);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

//prints a given action (from DEFINE)
void	print_action(t_meta *m, long long time, int philo_id, char *action)
{
	pthread_mutex_lock(&(m->o_mutex));
	printf("%lli : #%i %s\n", time, philo_id, action);
	if (action != ACT_DIE)
		pthread_mutex_unlock(&(m->o_mutex));
}

//converts a string into an interger
int	philo_atoi(const char *str, int allow_zero)
{
	int		i;
	int		number; //swap to long for bigger intervals?

	i = 0;
	number = 0;

	while ('0' <= str[i] && str[i] <= '9')
		number = (number * 10) + (str[i++] - '0');

	//printf("> Inputed value : %i\n", number); //DEBUG
	if (!str[i])
	{
		if (number > 0)
			return (number);
		else if (allow_zero && number == 0)
			return (number);
	}
	throw_error(ERR_A_VAL);
	return (-1);
}

//returns how long ago a specified time was (in ms)
long long	get_time_dif(long long then)
{
	struct timeval	t;
	int				now;

	gettimeofday(&t, NULL);

	now = (t.tv_sec * 1000) + (t.tv_usec / 1000); //current time in ms

	return (now - then);
}

//sleeps while checking for an end condition
int	smart_sleep(t_philo *p, int e_time)
{
	int	b_time; //in ns

	b_time = get_time_dif(0);
	while (get_time_dif(b_time) < e_time)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(SLEEP_T);
	}
	return (0);
}
