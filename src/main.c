/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/02 09:26:15 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//takes a pointer's adress and frees whatever is there, setting it to NULL after
void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

//initialises g_meta
t_meta	*init_meta(void)
{
	t_meta	*m;

	m = calloc(1, sizeof(t_meta));

	return (m);
}

//main function loop
int	philosopher(t_meta *m)
{
	return (0);
}

//entrypoint function
int	main(void) //int ac, char **av)
{
	t_meta	*m;
	int		exit_status;

	m = init_meta();

	exit_status = philosopher(m);

	free_null(ADRS m);
	return (exit_status);
}
