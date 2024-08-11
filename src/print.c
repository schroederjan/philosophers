/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:51:10 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 22:58:10 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_error(const char *msg, int return_code)
{
	printf(COLOR_RED "Error: %s\n" COLOR_RESET, msg);
	return (return_code);
}

const char*		get_color_for_status(const char *status) {
	if (ft_strncmp(status, "is thinking", 11) == 0)
		return COLOR_BLUE;
	else if (ft_strncmp(status, "is eating", 9) == 0)
		return COLOR_GREEN;
	else if (ft_strncmp(status, "is sleeping", 11) == 0)
		return COLOR_CYAN;
	else if (ft_strncmp(status, "has died", 7) == 0)
		return COLOR_RED;
	return COLOR_RESET;
}

void	print_status(t_data *data, int philo_id, const char *status)
{
	const char* color = get_color_for_status(status);

	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_running(data)) {
		color = get_color_for_status(status);
		printf("%s%ld %d %s%s\n", \
				color, \
				get_current_time() - data->simulation_start_time, \
				philo_id, \
				status, \
				COLOR_RESET);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	print_parse_error_usage(const char *program_name)
{
	printf(COLOR_RED "Error: Invalid number of arguments.\n" COLOR_RESET);
	printf(COLOR_YELLOW);
	printf("Usage: %s <args>\n", program_name);
	printf("Arguments:\n");
	printf("  1. number_of_philosophers\n");
	printf("  2. time_to_die (in milliseconds)\n");
	printf("  3. time_to_eat (in milliseconds)\n");
	printf("  4. time_to_sleep (in milliseconds)\n");
	printf("  5. [number_of_times_each_philosopher_must_eat] (optional)\n");
	printf(COLOR_RESET);
}

void	print_statistics(t_data *data)
{
	int i;
	int total_meals;

	total_meals = 0;
	i = 0;
	printf(COLOR_YELLOW "\n--- Simulation Statistics ---\n");
	while (i < data->num_philos)
	{
		printf("Philosopher %d ate %d meals\n", \
				data->philos[i].id, data->philos[i].meals_eaten);
		total_meals += data->philos[i].meals_eaten;
		i++;
	}
	printf("Total meals eaten: %d\n", total_meals);
	printf("Average meals per philosopher: %.2f\n", \
			(float)total_meals / data->num_philos);
	if (data->meals_required > 0)
	{
		printf("Required meals: %d\n", data->meals_required);
		if (total_meals >= data->num_philos * data->meals_required)
			printf(COLOR_GREEN "Simulation completed successfully\n");
		else
			printf(COLOR_RED "Simulation ended early\n");
	}
	printf(COLOR_YELLOW "----------------------------\n" COLOR_RESET);
}
