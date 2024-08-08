/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:46:46 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/08 15:57:44 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_or_full(t_philo *philo)
{
	if (philo->mind->meal_limit != -1)
	{
		pthread_mutex_lock(&philo->mind->m_meal);
		if (philo->mind->full_philos == philo->mind->philo_nbr)
		{
			pthread_mutex_unlock(&philo->mind->m_meal);
			return (1);
		}
		pthread_mutex_unlock(&philo->mind->m_meal);
	}
	pthread_mutex_lock(&philo->mind->m_end);
	if (philo->mind->end_flag == true)
	{
		pthread_mutex_unlock(&philo->mind->m_end);
		return (1);
	}
	pthread_mutex_unlock(&philo->mind->m_end);
	return (0);
}

static int	eat(t_philo *philo)
{
	if (philo->mind->end_flag == true)
		return (1);
	if (philo->mind->philo_nbr == 1)
	{
		ft_usleep(philo->mind->tt_die, philo);
		pthread_mutex_lock(&philo->mind->m_meal);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->mind->m_meal);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(&philo->mind->m_meal);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mind->m_meal);
	print_message(EATING, philo);
	ft_usleep(philo->mind->tt_eat, philo);
	philo->meals_consumed++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static int	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo);
	ft_usleep(philo->mind->tt_sleep, philo);
	print_message(THINKING, philo);
	return (0);
}

void *philo_roulette(void *ptr)
{
    t_philo		*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mind->m_roulette);
	pthread_mutex_unlock(&philo->mind->m_roulette);
	if (philo->id % 2 == 1)
	{
		print_message(THINKING, philo);
		ft_usleep(philo->mind->tt_eat, philo);
	}
	while (death_or_full(philo) == 0)
	{
		if (eat(philo) != 0)
			return (NULL);
		if (philo_sleep_think(philo) != 0)
			return (NULL);
	}
	return (NULL);
}
