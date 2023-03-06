/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/06 14:23:24 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// ======== LIBRARIES ======== //

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

// ======== DEFINITIONS ======== //

# define ERR_ARG	"Input Error : Invalid argument count"
# define ERR_NUM	"Input Error : Non-digit input are invalid"
# define ERR_INIT	"Process Error : Initialization failure"
# define ERR_MUT	"Process Error : Mutex failure"

# define ACT_TAKE	"has taken a fork";
# define ACT_EAT	"is eating";
# define ACT_SLEEP	"is sleeping";
# define ACT_THINK	"is thinking";
# define ACT_DIE	"died";

# define ADRS		(void **)&

// ======== ENUM STATES ======== //

enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_STARTING	= 0,
	MSTATE_RUNING	= 1,
	MSTATE_ENDING	= 2
};

enum e_pstate
{
	PSTATE_DEAD		= -1,
	PSTATE_SLEEPING	= 0,
	PSTATE_THINKING	= 1,
	PSTATE_EATING	= 2,
};

// ======== STRUCTS ======== //

typedef struct s_meta	t_meta;

typedef struct s_fork
{
	pthread_mutex_t	f_mutex;
	int				fork_id;
	int				user_id;
}					t_fork;

typedef struct s_philo
{
	t_meta	*m;
	t_fork	*right_fork;
	t_fork	*left_fork;

	int		philo_id;
	int		meal_count;

}			t_philo;

typedef struct s_meta
{
	int			philo_count;
	int			time_death;		//in ms
	int			time_eat;		//in ms
	int			time_sleep;		//in ms
	int			meal_limit;		//optional argument, ends program when reached by all philosophers

	pthread_t	*philo_threads;

	t_fork		**forks;
	t_philo		**philos;

	int			start_time;
	int			state;
}				t_meta;

// ======== FUNCTIONS ======== //

//from freeer
void	free_null(void **ptr);

#endif