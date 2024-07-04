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

typedef struct	s_overseer	t_overseer;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct	s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id; //a philo is a thread
	t_overseer		*overseer;
}	t_philo;

struct	s_overseer
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meal_limit;
	long	sim_start;
	long	sim_end; //when philo dies or all are full
	t_fork	*forks;
	t_philo	*philos;
};

void    error_exit(char *str);

#endif