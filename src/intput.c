/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intput.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:17:49 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/12 21:27:03 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_argument_string(const char *s)
{
	int		i;

	i = 0;
	if (s[0] == '0')
		return (print_error("Arguments must be greater than 0.", 1));
	while (s[i])
	{
		if (s[i] == '-' || (s[i] < '0' || s[i] > '9'))
			return (print_error("Arguments must be positive numbers only.", 1));
		i++;
	}
	if (i > 10)
		return (print_error("Number is too big (max 10 digits).", 1));
	return (SUCCESS);
}

static int	validate_arguments(t_data *data, int argc)
{
	if (data->num_philos < 1 || data->num_philos > 200)
		return (print_error(
				"Number of philosophers must be between 1 and 200.", 1));
	if (data->time_to_die < 60)
		return (print_error(
				"Time to die must be at least 60 ms.", 1));
	if (data->time_to_eat < 60)
		return (print_error(
				"Time to eat must be at least 60 ms.", 1));
	if (data->time_to_sleep < 60)
		return (print_error(
				"Time to sleep must be at least 60 ms.", 1));
	if (argc == 6 && data->meals_required < 1)
		return (print_error(
				"Number of meals must be at least 1.", 1));
	return (SUCCESS);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		print_parse_error_usage(argv[0]);
		return (ERROR);
	}
	while (i < argc)
	{
		if (validate_argument_string(argv[i]) != 0)
			return (ERROR);
		i++;
	}
	data->num_philos = atoi_positive_long(argv[1]);
	data->time_to_die = atoi_positive_long(argv[2]);
	data->time_to_eat = atoi_positive_long(argv[3]);
	data->time_to_sleep = atoi_positive_long(argv[4]);
	if (argc == 6)
		data->meals_required = atoi_positive_long(argv[5]);
	else
		data->meals_required = -1;
	return (validate_arguments(data, argc));
}
