/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intput.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:17:49 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 20:04:53 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int print_error(const char *msg, int return_code)
{
	printf("Error: %s\n", msg);
	return return_code;
}

static int validate_argument_string(const char *s)
{
	int i;

	i = 0;
	if (s[0] == '0')
		return print_error("Arguments must be greater than 0.", 1);
	while (s[i])
	{
		if (s[i] == '-' || (s[i] < '0' || s[i] > '9'))
			return print_error("Arguments must be positive numbers only.", 1);
		i++;
	}
	if (i > 10)
		return print_error("Number is too big (max 10 digits).", 1);
	return 0;
}

static int validate_arguments(t_data *data, int argc)
{
	if (data->num_philos < 1 || data->num_philos > 200)
		return print_error(
				"Number of philosophers must be between 1 and 200.", 1);
	if (data->time_to_die < 60)
		return print_error(
				"Time to die must be at least 60 ms.", 1);
	if (data->time_to_eat < 60)
		return print_error(
				"Time to eat must be at least 60 ms.", 1);
	if (data->time_to_sleep < 60)
		return print_error(
				"Time to sleep must be at least 60 ms.", 1);
	if (argc == 6 && data->meals_required < 1)
		return print_error(
				"Number of meals must be at least 1.", 1);
	return 0;
}

void print_parse_error_usage(const char *program_name)
{
    printf("Error: Invalid number of arguments.\n");
    printf("Usage: %s <args>\n", program_name);
    printf("Arguments:\n");
    printf("  1. number_of_philosophers\n");
    printf("  2. time_to_die (in milliseconds)\n");
    printf("  3. time_to_eat (in milliseconds)\n");
    printf("  4. time_to_sleep (in milliseconds)\n");
    printf("  5. [number_of_times_each_philosopher_must_eat] (optional)\n");
}

int parse_arguments(int argc, char **argv, t_data *data)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		print_parse_error_usage(argv[0]);
		return 1;
	}
	while (i < argc)
	{
		if (validate_argument_string(argv[i]) != 0)
			return 1;
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
	return validate_arguments(data, argc);
}
