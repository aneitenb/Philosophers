/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:23 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/08 14:47:00 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_data(t_overseer *data) // t_philo *philo
{
    philo = malloc(sizeof(t_philo));
    int i;

    i = 0;

    while (i < data->philo_nbr)
    {
        philo[i] = 
    }
    data->philos = malloc(sizeof(t_philo*) * data->philo_nbr);
}

int main(int argc, char **argv)
{
    t_overseer data;

    if (argc == 5 || argc == 6)
    {
        parse(&data, argv);
        init_data(&data);
        // philosophize(&data);
        // cleanup(&data);
    }
    else
        error_exit("Incorrect number of inputs");
    return (0);
}
