/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:53:59 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/05 18:19:22 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_master *mind)
{
    long    timer;
	int		i;
	unsigned int	current_time;
	
    while (1)
    {
		i = 0;
		while (i < mind->philo_nbr)
		{
			timer = mind->philo[i].last_meal_time - get_time() - mind->start_time;
			if (timer >= (long)mind->tt_die)
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
