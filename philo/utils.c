/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:33:04 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/11 17:38:10 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int kill(t_master *mind)
{
	int	i;

	i = 0;
	if (mind->philo == NULL || mind == NULL)
		return (0);
	while (i < mind->philo_nbr)
	{
		pthread_mutex_destroy(&mind->philo[i].right_fork);
		pthread_mutex_destroy(&mind->philo[i].thread_id);
		mind->philo[i].left_fork = NULL;
		mind->philo[i].master = NULL;
		i++;
	}
	pthread_mutex_destroy(&mind->m_print);
	free(mind->philo);
	mind->philo = NULL;
	return (0);
}
