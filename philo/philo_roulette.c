/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_roulette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:46:46 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/01 13:53:14 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	if (philo->mind->philo_nbr == 1)
	{
		ft_usleep(philo->mind->tt_die);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	print_message(EATING, philo);
	philo->last_meal_time = get_time();
	philo->meals_consumed++;
	ft_usleep(philo->mind->tt_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo);
	ft_usleep(philo->mind->tt_sleep);
	print_message(THINKING, philo);
}

void *philo_roulette(void *ptr)
{
    t_philo		*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->mind->tt_eat);
	while (philo->mind->end_flag == false)
	{
		if (eat(philo) != 0)
			break ;
		if (philo->meals_consumed == philo->mind->meal_limit)
		{
			philo->mind->full_philos++;
	        if (philo->mind->full_philos == philo->mind->philo_nbr)
		        philo->mind->end_flag = true;
			break ;
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
