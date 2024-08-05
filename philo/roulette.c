/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:46:46 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/05 18:14:27 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	die_and_end(t_philo *philo)
// {
// 	unsigned int	current_time;
	
// 	pthread_mutex_lock(&philo->mind->m_end);
// 	philo->mind->end_flag = true;
// 	pthread_mutex_unlock(&philo->mind->m_end);
// 	current_time = get_time() - philo->mind->start_time;
// 	pthread_mutex_lock(&philo->mind->m_print);
// 	printf("%u %d %s\n", current_time, philo->id + 1, DIED);
// 	pthread_mutex_unlock(&philo->mind->m_print);
// 	return (1);
// }

static int	eat(t_philo *philo)
{
	if (philo->mind->end_flag == true)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	if (philo->mind->philo_nbr == 1)
	{
		ft_usleep(philo->mind->tt_die, philo);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	print_message(EATING, philo);
	philo->last_meal_time = get_time() - philo->last_meal_time;
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
		ft_usleep(philo->mind->tt_eat - 10, philo);
	}
	while (philo->mind->end_flag == false)
	{
		if (eat(philo) != 0)
			break ;
		// if (philo->meals_consumed == philo->mind->meal_limit)
		// {
		// 	philo->mind->full_philos++;
	    //     if (philo->mind->full_philos == philo->mind->philo_nbr)
		// 	{
		// 		pthread_mutex_lock(&philo->mind->m_end);
		//         philo->mind->end_flag = true;
		// 		pthread_mutex_unlock(&philo->mind->m_end);
		// 		break ;
		// 	}
		// }
		if (philo_sleep_think(philo) != 0)
			break ;
	}
	return (NULL);
}
