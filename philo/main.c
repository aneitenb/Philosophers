/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:23 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/08 16:08:57 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static void	init_philos(t_overseer *data)
{
	int	i;

	i = 0;
	while(i < data->philo_nbr)
	{
		data->philos[i].id = i;
		data->philos[i].meals_count = 0;
		data->philos[i].full = false;
		data->philos[i].last_meal_time = 0;
		data->philos[i].overseer = data;
		data->philos[i].right_fork = malloc(sizeof(t_fork) * 1);
		 
	}
}   
 
static void	init_data(t_overseer *data) // t_philo *philo
{
    int	i;

    i = 0;
    data->end_flag = false;
    data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
    data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
    while (i < data->philo_nbr)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].id = i;
        i++;
    }
    init_philos(data);
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
