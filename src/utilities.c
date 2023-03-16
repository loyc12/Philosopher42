/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/16 10:27:58 by llord            ###   ########.fr       */
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
void	print_action(long long time, int philo_id, char *action)
{
	printf("%lli : #%i %s\n", time, philo_id, action);
}

//converts a string into an interger
int	philo_atoi(const char *str, int allow_zero)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while ('0' <= str[i] && str[i] <= '9')
		n = (n * 10) + (str[i++] - '0');
	if (!str[i])
	{
		if (n > 0)
			return (n);
		else if (allow_zero && n == 0)
			return (n);
	}
	throw_error(ERR_A_VAL);
	return (-1);
}

//returns how long ago a specified time was (in ms)
long	get_time_dif(long then)
{
	struct timeval	t;
	int				now;

	gettimeofday(&t, NULL);
	now = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (now - then);
}

//sleeps while checking for an end condition
int	smart_sleep(t_philo *p, int e_time)
{
	int	b_time;

	b_time = get_time_dif(0);
	while (get_time_dif(b_time) < e_time)
	{
		if (check_stop_flags(p))
			return (1);
		usleep(SLEEP_T);
	}
	return (0);
}
