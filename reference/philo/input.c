/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:12:00 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/23 19:37:27 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_num(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '0')
		return (ft_return("bigger than 0 plz"));
	while (s[i])
	{
		if (s[i] == '-' || (s[i] < '0' || s[i] > '9'))
			return (ft_return("positive only && numbers only"));
		i++;
	}
	if (i > 10)
		return (ft_return("number is too big"));
	return (SUCCESS);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (all_num(av[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static long	atoi_long(char *s)
{
	long	res;

	res = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res);
}

int	parse_input(t_data *data, char **av)
{
	data->num_philos = atoi_long(av[1]);
	if (data->num_philos > PHILO_MAX || data->num_philos < 1)
		return (ft_return("number of philos: 1 to 200"));
	data->time_to_die = atoi_long(av[2]);
	data->time_to_eat = atoi_long(av[3]);
	data->time_to_sleep = atoi_long(av[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (ft_return("timestamp >= 60 milliseconds"));
	if (av[5])
		data->meals_must_have = atoi_long(av[5]);
	else
		data->meals_must_have = -2;
	return (SUCCESS);
}
