/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/09 14:50:02 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int handle_error(int errno, t_master *mind)
{
    if (errno == ARG_COUNT)
        printf("Error: Incorrect number of arguments\n");
    else if (errno == INIT_ERROR)
	{
		if (mind->philo != NULL)
			free(mind->philo);
		printf("Error initialising\n");
	}
	else if (errno == PHILOS_ERROR)
	{
		printf("Error with threads\n");
		kill(mind);
	}
	return (errno);
}

int error_str(char *str)
{
    printf("%s\n", str);
    return (INVALID_ARG); 
}

char    *error_null(char *str)
{
    printf("%s\n", str);
    return (NULL); 
}
