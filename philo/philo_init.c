/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:10:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/02 12:33:21 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo(t_master *mind)
{
	int i;

	i = 0;
	while (i < mind->philo_nbr)
	{
		mind->philo[i].id = i;
		mind->philo[i].meals_consumed = 0;
		mind->philo[i].last_meal_time = mind->start_time;
		mind->philo[i].full = false;
        if (pthread_mutex_init(&mind->philo[i].left_fork, NULL) != 0)
			return (MUTEX_INIT_ERROR);
		mind->philo[i].right_fork = NULL;
        if (mind->philo_nbr > 1)
			mind->philo[i].right_fork = &mind->philo[(i + 1) % mind->philo_nbr].left_fork;
		if (pthread_create(&mind->philo[i].thread, NULL, \
			&philo_roulette, &mind->philo[i]) != 0)
			return (PHILOS_ERROR);
		printf("philo %d id: %d\n", i, mind->philo[i].id);
        i++;
    }
    return (0);
}

int init_data(t_master *mind)
{
    mind->full_philos = 0;
	mind->start_time = get_time();
	mind->end_flag = false;
	if (pthread_mutex_init(&mind->m_print, NULL))
		return (MUTEX_INIT_ERROR);
	mind->philo = malloc(sizeof(t_philo) * mind->philo_nbr);
	if (mind->philo == NULL)
		return (MALLOC_FAIL);
	return (0);
}
