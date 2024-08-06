/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:46:46 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/06 14:33:49 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	if (philo->mind->end_flag == true)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	print_message(EATING, philo);
	philo->last_meal_time = get_time() - philo->mind->start_time - philo->last_meal_time;
	printf("last meal time in philo %d : %lu\n", philo->id + 1, philo->last_meal_time);
	philo->meals_consumed++;
	ft_usleep(philo->mind->tt_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static int	philo_sleep_think(t_philo *philo)
{
	if (philo->mind->end_flag == true)
		return (1);
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
	while (philo->mind->end_flag == false)
	{
		if (philo->mind->philo_nbr == 1)
		{
			print_message(TAKES_FORK, philo);
			ft_usleep(philo->mind->tt_die, philo);
			break ;
		}
		if (eat(philo) != 0)
			break ;
		if (philo_sleep_think(philo) != 0)
			break ;
	}
	return (NULL);
}
