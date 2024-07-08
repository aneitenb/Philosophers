/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:55 by aneitenb          #+#    #+#             */
/*   Updated: 2024/07/08 18:18:30 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*check_valid_input(const char *str)
{
	int		len;
	int		i;
	const char	*number;

	i = 0;
	len = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
		str++;
	if (str[i] == '+')
		str++;
	else if (str[i] == '-')
		return(error_null("Error: Use positive number input"));
	if (str[i] < '0' || str[i] > '9' )
		return(error_null("Error: Use only numbers as input"));
	number = str;
	while(str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	if (len > 10)
		return(error_null("Error: Do not input numbers greater than INT_MAX"));
	return (number);	
}

static long	ft_atol(const char *str)
{
	long	num;
	
	num = 0;
	str = check_valid_input(str);
	if (str == NULL)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		return (error_str("Error: Do not input numbers greater than INT_MAX"));
	return (num);
}

int	parse(t_overseer *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->philo_nbr < 0 || data->time_to_die < 0 || 
		data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (-1);
	if (argv[5])
	{
		data->meal_limit = ft_atol(argv[5]);
		if (data->meal_limit < 0)
			return (-1);
	}
	else
		data->meal_limit = -1;
	if (data->philo_nbr == 0 || data->time_to_die == 0 || data->time_to_eat == 0
		|| data->time_to_sleep == 0 || data->meal_limit == 0)
		return (error_str("Error: Inputs cannot be 0"));
	printf("philo nbr: %lu\n tt die: %lu\n tt eat: %lu\n tt sleep: %lu\n meals: %d\n",
		data->philo_nbr, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->meal_limit);
	return (0);
}
