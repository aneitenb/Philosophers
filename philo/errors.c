/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/08 17:20:57 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int error_str(char *str)
{
    printf("%s\n", str);
    return (-1); 
}

char    *error_null(char *str)
{
    printf("%s\n", str);
    return (NULL); 
}
