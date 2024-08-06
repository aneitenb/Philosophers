/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:53:59 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/06 14:24:11 by aneitenb         ###   ########.fr       */
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
	mind->start_time = get_time();
	pthread_mutex_unlock(&mind->m_roulette);
	monitoring(mind);
	return (0);
}

void	monitoring(t_master *mind)
{
	int				i;
	unsigned int	current_time;
	
    while (1)
    {
		i = 0;
		while (i < mind->philo_nbr && mind->end_flag == false)
		{
			if ((long)mind->philo[i].last_meal_time >= (long)mind->tt_die)
			{
				pthread_mutex_lock(&mind->m_end);
				mind->end_flag = true;
				pthread_mutex_unlock(&mind->m_end);
				current_time = get_time() - mind->start_time;
				pthread_mutex_lock(&mind->m_print);
				printf("%u %d %s\n", current_time, mind->philo[i].id + 1, DIED);
				pthread_mutex_unlock(&mind->m_print);
				break ;
			}
			if (mind->philo[i].meals_consumed == mind->philo[i].mind->meal_limit)
			{
				mind->full_philos++;
				if (mind->full_philos == mind->philo_nbr)
				{
					pthread_mutex_lock(&mind->m_end);
					mind->end_flag = true;
					pthread_mutex_unlock(&mind->m_end);
					break ;
				}
			}
			i++;
		}
    }
}
