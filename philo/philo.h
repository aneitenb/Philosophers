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
# define INVALID_ARG		201
# define INIT_ERROR			202
# define PHILOS_ERROR		203
# define MALLOC_FAIL		204
# define MUTEX_INIT_ERROR	205

typedef struct	s_master	t_master;

typedef struct	s_philo
{
	int				id;
	long			meals_consumed;
	size_t			last_meal_time;
	size_t			start_time; //
	bool			full;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread; //a philo is a thread
	t_master		*mind;
}	t_philo;

struct	s_master
{
	long			philo_nbr;
	size_t			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			meal_limit;
	long			full_philos;
	// size_t			start_time;
	bool			end_flag; //when philo dies or all are full
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_roulette;
	t_philo			*philo;
};

int 	error_str(char *str);
char    *error_null(char *str);
int		check_arg(t_master *data, char **argv);
int 	handle_error(int errno, t_master *mind);
int 	init_data(t_master *mind);
int 	init_philo(t_master *mind);
void 	*philo_roulette(void *ptr);
void	print_message(char *str, t_philo *philo);
void	ft_usleep(unsigned int time, t_philo *philo);
size_t	get_time(void);
int 	kill(t_master *mind);
void	monitoring(t_master *mind);
int		create_threads(t_master *mind);
int		death_or_full(t_philo *philo);

#endif