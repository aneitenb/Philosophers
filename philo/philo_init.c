/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:10:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/01 14:01:17 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_master *mind)
{
	int	i;

	i = 0;
	while (i < mind->philo_nbr)
	{
		if (pthread_create(&mind->philo[i].thread_id, NULL, \
			&philo_roulette, &mind->philo[i]) != 0)
			return (PHILOS_ERROR);
		i++;
	}
	return (0);
}

int init_philo(t_master *mind)
{
    int i;
    
    i = 0;
    printf("philo nbr: %ld\n", mind->philo_nbr);
    while (i < mind->philo_nbr)
    {
        mind->philo[i].id = i;
        mind->philo[i].meals_consumed = 0;
        mind->philo[i].full = false;
        mind->philo[i].last_meal_time = mind->start_time;
        mind->philo[i].right_fork = NULL;
        if (pthread_mutex_init(&mind->philo[i].left_fork, NULL) != 0)
            return (MUTEX_INIT_ERROR);
        if (mind->philo_nbr > 1)
			mind->philo[i].right_fork = &mind->philo[(i + 1) % mind->philo_nbr].left_fork;
        i++;
    }
    if (create_threads(mind) != 0)
        return(PHILOS_ERROR);
    return (0);
}

int init_data(t_master *mind)
{
    mind->start_time = get_time();
    mind->end_flag = false;
    mind->philo = malloc(sizeof(t_philo) * mind->philo_nbr);
    mind->full_philos = 0;
    if (mind->philo == NULL)
        return (MALLOC_FAIL);
    if (pthread_mutex_init(&mind->m_print, NULL))
        return (MUTEX_INIT_ERROR);
    return (0);
}
