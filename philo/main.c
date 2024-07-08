/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:23 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/08 10:36:30 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_overseer data;

    if (argc == 5 || argc == 6)
    {
        parse(&data, argv);
        // init_data(&data);
        // philosophize(&data);
        // cleanup(&data);
    }
    else
        error_exit("Incorrect input");
    return (0);
}
