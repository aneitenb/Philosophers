/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:53:59 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/08 21:20:37 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_master *mind)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&mind->m_roulette);
	while(i < mind->philo_nbr)
	{
		if (pthread_create(&mind->philo[i].thread, NULL, \
			&philo_roulette, &mind->philo[i]) != 0)
			return (PHILOS_ERROR);
		i++;
	}
	// mind->start_time = get_time();
	pthread_mutex_unlock(&mind->m_roulette);
	i = 0;
	while (i < mind->philo_nbr)
	{
		if (pthread_join(mind->philo[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	monitoring(mind);
	return (0);
}

void	philo_has_died(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->mind->m_print);
	time = get_time() - philo->start_time;
	printf("%u %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->mind->m_print);
}

static int	monitor_death(t_master *mind, int i)
{
	size_t	time;
	
	pthread_mutex_lock(&mind->m_meal);
	time = get_time() - mind->philo[i].last_meal_time;
	if (time >= mind->tt_die)
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
	int	i;

	i = 0;
	while (i < mind->philo_nbr)
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
		i++;
	}
	return (0);
}

void	monitoring(t_master *mind)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		while (i < mind->philo_nbr)
		{
			if (monitor_death(mind, i))
				break ;
			if (mind->meal_limit != -1)
			{
				if (monitor_full_philos(mind, i))
					break ;
			}
			i++;
		}
	}
}


// void	monitoring(t_master *mind)
// {
// 	int				i;
// 	unsigned int	current_time;
	
//     while (1)
//     {
// 		i = 0;
// 		while (i < mind->philo_nbr && mind->end_flag == false)
// 		{
// 			if ((long)mind->philo[i].last_meal_time >= (long)mind->tt_die)
// 			{
// 				pthread_mutex_lock(&mind->m_end);
// 				mind->end_flag = true;
// 				pthread_mutex_unlock(&mind->m_end);
// 				current_time = get_time() - mind->philo[i].start_time;
// 				pthread_mutex_lock(&mind->m_print);
// 				printf("%u %d %s\n", current_time, mind->philo[i].id + 1, DIED);
// 				pthread_mutex_unlock(&mind->m_print);
// 				return ;
// 			}
// 			pthread_mutex_lock(&mind->m_meal);
// 			if (mind->philo[i].meals_consumed == mind->meal_limit)
// 			{
// 				mind->full_philos++;
// 				if (mind->full_philos == mind->philo_nbr)
// 				{
// 					pthread_mutex_lock(&mind->m_end);
// 					mind->end_flag = true;
// 					pthread_mutex_unlock(&mind->m_end);
// 					pthread_mutex_unlock(&mind->m_meal);
// 					return ;
// 				}
// 				pthread_mutex_unlock(&mind->m_meal);
// 			}
// 			i++;
// 		}
//     }
// }
