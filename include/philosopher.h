/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/01 14:41:54 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// ======== LIBRARIES ======== //

# include "../libft/libft.h"
# include <stdio.h>

// ======== ERROR MESSAGES ======== //

# define ERR_PIPE	"Process Error : Couldn't pipe() properly\n"
# define ERR_FORK	"Process Error : Couldn't fork() properly\n"
# define ERR_EXIT	"Process Warning : Child did not exit properly\n"

# define ERR_ARG	"Input Error : Invalid argument given\n"
# define ERR_ARG_NB	"Input Error : Invalid argument number\n"
# define ERR_QUOTES	"Input Error : Invalid quotation (unclosed)\n"

# define ADRS		(void **)&

// ======== ENUM STATES ======== //

enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_RUNING	= 0,
	MSTATE_STARTING	= 1,
	MSTATE_ENDING	= 2
};

// ======== STRUCTS ======== //

typedef struct s_meta
{
	int		state;
}			t_meta;

// ======== GLOBAL VAR ======== //

t_meta		*g_meta;

// ======== FUNCTIONS ======== //

#endif