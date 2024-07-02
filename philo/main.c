/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:23 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/02 16:55:08 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_input data;

    if (argc == 5 || argc == 6)
    {
        if (parse(&data, argv) < 0)
            error_exit("Incorrect input");
        init_data(&data);
        philosophize(&data);
        cleanup(&data);
    }
    else
        error_exit("Incorrect input");
    return (0);
}
