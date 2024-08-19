/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:47:59 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/19 15:11:38 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_has_died(t_philo *philo, char *str)
{
	unsigned int	time;

	pthread_mutex_lock(&philo->mind->m_print);
	time = get_time() - philo->mind->start_time;
	printf("%u %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->mind->m_print);
}

int	check_full(t_master *mind, int i)
{
	pthread_mutex_lock(&mind->m_meal);
	if (mind->philo[i].meals_consumed == mind->meal_limit)
	{
		pthread_mutex_unlock(&mind->m_meal);
		return (1);
	}
	pthread_mutex_unlock(&mind->m_meal);
	return (0);
}

static int	monitor_full_philos(t_master *mind, int i)
{
	if (check_full(mind, i))
	{
		pthread_mutex_lock(&mind->m_meal);
		if (mind->philo[i].meals_consumed == mind->meal_limit)
			mind->full_philos++;
		if (mind->full_philos == mind->philo_nbr)
		{
			pthread_mutex_unlock(&mind->m_meal);
			return (1);
		}
		pthread_mutex_unlock(&mind->m_meal);
	}
	return (0);
}

static int	monitor_death(t_master *mind, int i)
{
	size_t	time;

	pthread_mutex_lock(&mind->m_meal);
	time = get_time() - mind->philo[i].last_meal_time;
	if (time >= (size_t)mind->tt_die)
	{
		pthread_mutex_lock(&mind->m_end);
		mind->end_flag = true;
		pthread_mutex_unlock(&mind->m_end);
		pthread_mutex_unlock(&mind->m_meal);
		philo_has_died(&mind->philo[i], DIED);
		return (1);
	}
	pthread_mutex_unlock(&mind->m_meal);
	return (0);
}

void	monitoring(t_master *mind)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < mind->philo_nbr)
		{
			if (monitor_death(mind, i))
				return ;
			if (mind->meal_limit != -1)
			{
				if (monitor_full_philos(mind, i))
					return ;
			}
			i++;
		}
	}
}
