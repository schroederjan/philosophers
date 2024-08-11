/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:50 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 21:49:28 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int		main(int argc, char **argv)
{
	t_data data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (ERROR);
	if (initialize_simulation(&data) != 0)
		return (ERROR);
	start_simulation(&data);
	print_statistics(&data);
	cleanup_simulation(&data);
	return (SUCCESS);
}
