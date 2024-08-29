/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:53:59 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/29 16:07:13 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_master *mind)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&mind->m_roulette);
	while (i < mind->philo_nbr)
	{
		if (pthread_create(&mind->philo[i].thread, NULL, \
			&philo_roulette, &mind->philo[i]) != 0)
			return (PHILOS_ERROR);
		i++;
	}
	pthread_mutex_unlock(&mind->m_roulette);
	i = 0;
	monitoring(mind);
	while (i < mind->philo_nbr)
	{
		if (pthread_join(mind->philo[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}
