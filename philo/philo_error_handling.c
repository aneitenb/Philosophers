/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/29 11:33:19 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_error(int errno, t_master *mind)
{
	if (errno == ARG_COUNT)
		printf("Error: Incorrect number of arguments\n");
	else if (errno == INVALID_ARG)
	{
		printf("Error: Invalid arguments\n");
	}
	else if (errno == INIT_ERROR)
	{
		if (mind->philo != NULL)
			free(mind->philo);
		printf("Error initialising\n");
	}
	else if (errno == PHILOS_ERROR)
	{
		kill(mind);
		printf("Error with threads\n");
	}
	return (errno);
}
