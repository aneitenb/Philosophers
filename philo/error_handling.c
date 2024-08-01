/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/01 13:55:20 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int handle_error(int errno, t_master *mind)
{
    if (errno == ARG_COUNT)
        (void)write(2, "Error: Incorrect number of arguments\n", 37);
    else if (errno == INIT_ERROR)
	{
		if (mind->philo != NULL)
			free(mind->philo);
		(void)!write(2, "Error initialising\n", 20);
	}
	else if (errno == PHILOS_ERROR)
	{
		(void)!write(2, "Error with threads\n", 20);
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
