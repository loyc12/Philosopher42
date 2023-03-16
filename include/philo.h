/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/16 13:10:50 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ======== LIBRARIES ======== //

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// ======== DEFINITIONS ======== //

# define ERR_A_CNT	"Input Error : Invalid argument count"
# define ERR_A_VAL	"Input Error : Values have to greater than 0"
# define ERR_P_NONE	"Input Error : I am not, therefore I think not"
# define ERR_P_CNT	"Input Error : Cannot seat this many philosophers"
# define ERR_INIT	"Process Error : Initialization failure"
# define ERR_ACTION	"Process Error : Invalid value given"
# define ERR_THREAD	"Process Error : Thread failure"
# define ERR_MUTEX	"Process Error : Mutex failure"

# define ACT_TAKE	"has taken a fork"
# define ACT_EAT	"is eating"
# define ACT_SLEEP	"is sleeping"
# define ACT_THINK	"is thinking"
# define ACT_DIE	"died"

# define ADRS		(void **)&
# define ADRS2		(void ***)&

# define BORN_T		(int)5 //(in usec) interval during philosopher creation
# define SLEEP_T	(int)1000 //(in usec) interval during death checks when doing action
# define PHILO_M	(int)200 //max number of philosophers

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
	PSTATE_ALIVE	= 0,
	PSTATE_DEAD		= 1
};

// ======== STRUCTS ======== //

typedef struct s_meta	t_meta;

typedef struct s_fork
{
	int				fork_id;
	int				user_id;

	pthread_mutex_t	f_mutex;		//mutext for fork usage
}					t_fork;

typedef struct s_philo
{
	t_meta			*m;
	t_fork			*right_fork;
	t_fork			*left_fork;

	long long		last_meal;
	int				meal_count;
	int				philo_id;

	pthread_mutex_t	p_mutex;		//mutex for philo's meal_count and state
	int				state;

}			t_philo;

typedef struct s_meta
{
	int				philo_count;
	int				time_death;		//in ms
	int				time_eat;		//in ms
	int				time_sleep;		//in ms
	int				time_think;		//in ms
	int				meal_limit;		//optional argument, ends program when reached by all philosophers

	pthread_t		**threads;

	t_fork			**forks;
	t_philo			**philos;

	long long		start_time;		//in ms

	pthread_mutex_t	m_mutex;		//mutex for meta's state
	pthread_mutex_t	o_mutex;		//mutex for outputing to terminal
	int				state;
}					t_meta;

// ======== FUNCTIONS ======== //

//from acter
int			think_n_check(t_philo *p);
void		live(t_philo *p);

//from checkers
void		make_checks(t_meta *m);
int			check_stop_flags(t_philo *p);
void		find_time_think(t_meta *m);

//from initializers
void		init_forks(t_meta *m);
void		init_philos(t_meta *m);
int			init_meta(t_meta *m, char **av);

//from killers
void		free_null(void **ptr);
void		free_array(void ***ptr);
void		free_all(t_meta *m);
void		wait_threads(t_meta *m);
void		kill_mutex(t_meta *m);

//from main
void		*philosopher(void *void_philo);
void		start_threads(t_meta *m);

//from utilities
int			throw_error(char *error);
void		print_action(t_meta *m, long long time, int philo_id, char *action);
int			philo_atoi(const char *str, int allow_zero);
long long	get_time_dif(long long time);
int			smart_sleep(t_philo *p, int e_time);

#endif