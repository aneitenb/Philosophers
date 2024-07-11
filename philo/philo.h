#ifndef PHILO_H
# define PHILO_H

/*	printf	*/
#include <stdio.h>

/*	malloc, free	*/
#include <stdlib.h>

/*	write, usleep	*/
#include <unistd.h>
#include <stdbool.h>

/*	mutex (init, destroy, lock, unlock)	*
*	threads (create, join, detach)		*/
#include <pthread.h>

/*	INT_MAX	*/
#include <limits.h>

/*	gettimeofday	*/
#include <sys/time.h>

# define TAKES_FORK			"has taken a fork"
# define EATING				"is eating"
# define SLEEPING			"is sleeping"
# define THINKING			"is thinking"
# define DIED				"died"
# define ARG_COUNT			200
# define INVALID_ARG		201//
# define INIT_ERROR			202
# define PHILOS_ERROR		203
# define MALLOC_FAIL		204
# define MUTEX_INIT_ERROR	205

typedef struct	s_master	t_master;

/* philo[i]->right_fork = malloc(sizeof(t_fork) * data->philo_nbr) 
if (philo[i] == 0)
	philo->left_fork = philo[data->philo_nbr]->right_fork;
else
	philo[i]->left_fork = philo[i + 1]->right_fork*/

typedef struct	s_philo
{
	int				id;
	long			meals_consumed;
	bool			full;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id; //a philo is a thread
	t_master			*master;
}	t_philo;

struct	s_master
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	long			start;
	pthread_mutex_t	m_print;
	bool			end_flag; //when philo dies or all are full
	t_philo			*philo;
};

int 	error_str(char *str);
char    *error_null(char *str);
int		check_arg(t_master *data, char **argv);
int 	handle_error(int errno, t_master *mind);
int 	init_data(t_master *mind);
int 	init_philo(t_master *mind);

#endif