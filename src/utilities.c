/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/08 10:38:25 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	printf("%lli : %i %s\n", time, philo_id, action);
}

//converts a string into an interger
int	ft_atoi(const char *str)
{
	int		i;
	int		number; //swap to long for bigger intervals?

	i = 0;
	number = 0;

	while ('0' <= str[i] && str[i] <= '9')
		number = (number * 10) + (str[i++] - '0');

	printf("> Inputed value : %i\n", number); //DEBUG

	if (!str[i])
		return (number);
	throw_error(ERR_A_VAL);
	return (-1);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);

	return ((t.tv_sec * 1000) + (t.tv_usec / 1000)); //returns time in ms
}

long long	time_dif(t_meta *m)
{
	return (get_time() - m->start_time); //returns time dif in ms
}
