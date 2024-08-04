/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:33:04 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/04 15:36:20 by aneitenb         ###   ########.fr       */
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
		printf("Error in get time of day\n");
		return (1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(unsigned int time, t_philo *philo)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < time && philo->mind->end_flag == false)
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
	while (i < mind->philo_nbr)
	{
		if (pthread_join(mind->philo[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	printf("2.5\n");
	return (0);
}
