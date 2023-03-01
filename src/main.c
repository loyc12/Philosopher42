/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 13:09:04 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//our global var
t_meta	*g_meta;

//initialises g_meta
void	init_meta(void)
{
	g_meta = calloc(1, sizeof(t_meta));
}

int	philosopher(void)
{
	return (0);
}

//entrypoint function
int	main(void) //int ac, char **av)
{
	int	exit_status;

	init_meta();

	exit_status = philosopher();

	ft_free_null(g_meta);
	return (exit_status);
}
