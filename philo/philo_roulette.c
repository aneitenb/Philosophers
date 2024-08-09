/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_roulette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:46:46 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/09 15:28:47 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_or_full(t_philo *philo)
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

// static void	dine_time(t_philo *philo)
// {
// 	print_message(EATING, philo);
// 	ft_usleep(philo->mind->tt_eat, philo);
// 	pthread_mutex_lock(&philo->mind->m_meal);
// 	philo->last_meal_time = get_time();
// 	philo->meals_consumed++;
// 	pthread_mutex_unlock(&philo->mind->m_meal);
// 	pthread_mutex_unlock(&philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// }

static void	singles_fate(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	ft_usleep(philo->mind->tt_die, philo);
	pthread_mutex_lock(&philo->mind->m_end);
	philo->mind->end_flag = true;
	pthread_mutex_unlock(&philo->mind->m_end);
	pthread_mutex_unlock(&philo->left_fork);
}

static int	eat(t_philo *philo)
{
	printf("entering eat\n");
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	print_message(EATING, philo);
	ft_usleep(philo->mind->tt_eat, philo);
	pthread_mutex_lock(&philo->mind->m_meal);
	philo->last_meal_time = get_time();
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->mind->m_meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	printf("EXITING eat\n");
	return (0);
}

	// if (death_or_full(philo))
	// 	return (1);
	// else
	// {
	// 	pthread_mutex_lock(&philo->left_fork);
	// 	print_message(TAKES_FORK, philo);
	// }
	// if (death_or_full(philo))
	// {
	// 	printf("WE DIED OR FULL\n");
	// 	return (1);
	// }
	// else
	// {
	// 	printf("PHILO %d GONNA PICK UP LEFT\n", philo->id + 1);
	// 	pthread_mutex_lock(philo->right_fork);
	// 	print_message(TAKES_FORK, philo);
	// }
	// if (death_or_full(philo))
	// {
	// 	pthread_mutex_unlock(&philo->left_fork);
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	return (1);
	// }
	// else
	// 	dine_time(philo);
	// return (0);
// }

//	in philo_roulette:
	// while (1)
	// {
	// 	if (eat(philo) != 0)
	// 		return (NULL);
	// 	if (philo_sleep(philo) != 0)
	// 		return (NULL);
	// 	print_message(THINKING, philo);
	// }
	

static int	philo_sleep(t_philo *philo)
{
	printf("entering sleep\n");
	print_message(SLEEPING, philo);
	ft_usleep(philo->mind->tt_sleep, philo);
	printf("EXITING SLEEP\n");
	return (0);
}

void *philo_roulette(void *ptr)
{
    t_philo		*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mind->m_roulette);
	pthread_mutex_unlock(&philo->mind->m_roulette);
	if (philo->mind->philo_nbr == 1)
	{
		singles_fate(philo);
		return (NULL);
	}
	if (philo->id % 2 == 1)
	{
		print_message(THINKING, philo);
		ft_usleep(philo->mind->tt_eat - 10, philo);
	}
	while (death_or_full(philo) == 0)
	{
		if (eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		print_message(THINKING, philo);
	}
	return (NULL);
}