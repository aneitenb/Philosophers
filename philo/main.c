/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:23 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/05 17:24:58 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_master    mind;
    
    if (argc != 5 && argc != 6)
        return (handle_error(ARG_COUNT, &mind));
    if (check_arg(&mind, argv) != 0)
        return (INVALID_ARG);
    if (init_data(&mind) != 0)
        return (handle_error(INIT_ERROR, &mind));
    if (init_philo(&mind) != 0)
        return (handle_error(PHILOS_ERROR, &mind));
    if (join_threads(&mind) != 0)
		return (handle_error(PHILOS_ERROR, &mind));
    kill(&mind);
    return (0);
}
