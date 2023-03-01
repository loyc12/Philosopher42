/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 14:40:32 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//our global var
t_meta	*g_meta;

//takes a pointer's adress and frees whatever is there, setting it to NULL after
void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

//initialises g_meta
void	init_meta(void)
{
	g_meta = calloc(1, sizeof(t_meta));
}

//main function loop
int	philosopher(void)
{
	free_null((void **)&g_meta);
	return (0);
}

//entrypoint function
int	main(void) //int ac, char **av)
{
	int	exit_status;

	init_meta();

	exit_status = philosopher();

	free_null((void **)&g_meta);
	return (exit_status);
}
