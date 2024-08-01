/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:33:04 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/01 13:49:43 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	unsigned int	current_time;

	if (philo->mind->end_flag == true)
		return ;
	current_time = get_time() - philo->mind->start_time;
	pthread_mutex_lock(&philo->mind->m_print);
	printf("%u %d %s\n", current_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->mind->m_print);
}

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		write(2, "Error in get time of day", 24);
		return (1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(unsigned int time)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

int kill(t_master *mind)
{
	int	i;

	i = 0;
	if (mind->philo == NULL || mind == NULL)
		return (0);
	while (i < mind->philo_nbr)
	{
		pthread_mutex_destroy(&mind->philo[i].left_fork);
		mind->philo[i].right_fork = NULL;
		mind->philo[i].mind = NULL;
		i++;
	}
	pthread_mutex_destroy(&mind->m_print);
	free(mind->philo);
	mind->philo = NULL;
	return (0);
}

int	join_threads(t_master *mind)
{
	printf("2\n");
	int	i;

	i = 0;
	printf("philo nbr: %ld", mind->philo_nbr);
	while (i < mind->philo_nbr)
	{
		if (pthread_join(mind->philo[i].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
		printf("i: %d", i);
	}
	return (0);
}
