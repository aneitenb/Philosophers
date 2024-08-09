/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:33:04 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/09 15:40:27 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	unsigned int	current_time;

	pthread_mutex_lock(&philo->mind->m_end);
	if (philo->mind->end_flag == true)
	{
		pthread_mutex_unlock(&philo->mind->m_end);	
		return ;
	}
	pthread_mutex_unlock(&philo->mind->m_end);
	pthread_mutex_lock(&philo->mind->m_print);
	current_time = get_time() - philo->start_time;
	printf("%u %d %s\n", current_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->mind->m_print);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf("Error in gettimeofday\n");
		return (1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(unsigned int time, t_philo *philo)
{
	size_t	start;
	size_t	dead;
	
	start = get_time();
	// pthread_mutex_lock(&philo->mind->m_meal);
	dead = philo->last_meal_time + philo->mind->tt_die;
	// pthread_mutex_unlock(&philo->mind->m_meal);
	while (((get_time() - start) < time) && get_time() < dead)
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