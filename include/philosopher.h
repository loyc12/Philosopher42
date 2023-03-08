/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/08 10:45:21 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// ======== LIBRARIES ======== //

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// ======== DEFINITIONS ======== //

# define ERR_A_CNT	"Input Error : Invalid argument count"
# define ERR_A_VAL	"Input Error : Values have to be unsigned intergers"
# define ERR_P_NONE	"Input Error : I am not, therefore I think not"
# define ERR_P_CNT	"Input Error : Cannot seat this many philosophers"
# define ERR_INIT	"Process Error : Initialization failure"
# define ERR_ACTION	"Process Error : Invalid value given"
# define ERR_THREAD	"Process Error : Thread failure"
# define ERR_MUTEX	"Process Error : Mutex failure"

# define ACT_BORN	"has been born"
# define ACT_TAKE	"has taken a fork"
# define ACT_EAT	"is eating"
# define ACT_SLEEP	"is sleeping"
# define ACT_THINK	"is thinking"
# define ACT_DIE	"died"

# define ADRS		(void **)&
# define ADRS2		(void ***)&

# define THREAD_W	(int)5 //wait between thread starts (in us)
# define PHILO_M	(int)1000 //max number of philosophers

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
	PSTATE_STARTING	= 0,
	PSTATE_SLEEPING	= 1,
	PSTATE_THINKING	= 2,
	PSTATE_EATING	= 3,
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
	t_meta		*m;
	t_fork		*right_fork;
	t_fork		*left_fork;

	int			philo_id;
	int			meal_count;
	int			state;

}			t_philo;

typedef struct s_meta
{
	int			philo_count;
	int			time_death;		//in ms
	int			time_eat;		//in ms
	int			time_sleep;		//in ms
	int			meal_limit;		//optional argument, ends program when reached by all philosophers

	pthread_t	**p_threads;

	t_fork		**forks;
	t_philo		**philos;

	long long	start_time;
	int			state;
}				t_meta;

// ======== FUNCTIONS ======== //

//from main
void		*philosopher(void *void_philo);

//from killers
void		free_null(void **ptr);
void		free_array(void ***ptr);
void		free_all(t_meta *m);
void		kill_threads(t_meta *m);
void		kill_mutex(t_meta *m);

//from utilities
int			throw_error(char *error);
void		print_action(long long time, int philo_id, char *action);
int			ft_atoi(const char *str);

//from initializers
void		start_threads(t_meta *m);
void		init_forks(t_meta *m);
void		init_philos(t_meta *m);
int			init_meta(t_meta *m, char **av);
long long	get_time(void);
long long	time_dif(t_meta *m);

//from acter
void		do_action(t_philo *p, int new_state);

#endif