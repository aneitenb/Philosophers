/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:55 by aneitenb          #+#    #+#             */
/*   Updated: 2024/08/19 17:58:04 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_master *mind)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_time();
	while (i < mind->philo_nbr)
	{
		mind->philo[i].mind = mind;
		mind->philo[i].id = i;
		mind->philo[i].meals_consumed = 0;
		mind->philo[i].last_meal_time = time;
		mind->start_time = time;
		mind->philo[i].full = false;
		if (pthread_mutex_init(&mind->philo[i].right_fork, NULL) != 0)
			return (MUTEX_INIT_ERROR);
		mind->philo[i].left_fork = NULL;
		if (mind->philo_nbr > 1)
			mind->philo[i].left_fork = &mind->philo[(i + 1) % \
			mind->philo_nbr].right_fork;
		i++;
	}
	return (0);
}

int	init_data(t_master *mind)
{
	mind->full_philos = 0;
	mind->end_flag = false;
	if (pthread_mutex_init(&mind->m_print, NULL))
		return (MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&mind->m_end, NULL))
		return (MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&mind->m_roulette, NULL))
		return (MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&mind->m_meal, NULL))
		return (MUTEX_INIT_ERROR);
	mind->philo = malloc(sizeof(t_philo) * mind->philo_nbr);
	if (mind->philo == NULL)
		return (MALLOC_FAIL);
	return (0);
}

static const char	*check_valid_input(const char *str)
{
	int			len;
	int			i;
	const char	*number;

	i = 0;
	len = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	if (str[i] == '+')
		str++;
	else if (str[i] == '-')
		return (NULL);
	if (str[i] < '0' || str[i] > '9')
		return (NULL);
	number = str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	if (len > 10)
		return (NULL);
	if (str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
		return (NULL);
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
		return (-1);
	return (num);
}

int	check_arg(t_master *mind, char **argv)
{
	mind->philo_nbr = ft_atol(argv[1]);
	mind->tt_die = ft_atol(argv[2]);
	mind->tt_eat = ft_atol(argv[3]);
	mind->tt_sleep = ft_atol(argv[4]);
	if ((int)mind->tt_die < 0 || (int)mind->philo_nbr < 0
		|| (int)mind->tt_eat < 0 || (int)mind->tt_sleep < 0)
		return (INVALID_ARG);
	if (argv[5])
	{
		mind->meal_limit = ft_atol(argv[5]);
		if (mind->meal_limit < 0)
			return (INVALID_ARG);
	}
	else
		mind->meal_limit = -1;
	if (mind->philo_nbr == 0 || mind->tt_die == 0 || mind->tt_eat == 0
		|| mind->tt_sleep == 0 || mind->meal_limit == 0)
		return (INVALID_ARG);
	return (0);
}
