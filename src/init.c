/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:15:30 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/22 20:56:07 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_chopsticks(\
		t_philo *philo, t_chopstick *chopsticks, int num_philos)
{
	philo->left_chopstick = &chopsticks[philo->id - 1];
	philo->right_chopstick = &chopsticks[philo->id % num_philos];
}

static int	init_philos(t_data *data)
{
	int		i;
	long	current_time;

	current_time = get_current_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].has_eaten_enough = false;
		data->philos[i].last_meal_time = current_time;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (print_error("Philosopher mutex initialization failed", 1));
		assign_chopsticks(&data->philos[i], data->chopsticks, data->num_philos);
		i++;
	}
	return (SUCCESS);
}

static int	init_chopsticks(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->chopsticks[i].mutex, NULL) != 0)
			return (print_error("Chopstick mutex initialization failed", 1));
		data->chopsticks[i].id = i + 1;
		i++;
	}
	return (SUCCESS);
}

static int	init_data(t_data *data)
{
	data->simulation_running = false;
	data->time_to_think = (\
						data->time_to_die - \
						data->time_to_eat - \
						data->time_to_sleep) / 2;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || \
			pthread_mutex_init(&data->simulation_mutex, NULL) != 0)
		return (print_error("Simulation mutex initialization failed", 1));
	data->simulation_start_time = get_current_time();
	return (SUCCESS);
}

int	initialize_simulation(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->chopsticks = malloc(sizeof(t_chopstick) * data->num_philos);
	if (!data->philos || !data->chopsticks)
		return (print_error("Memory allocation failed", 1));
	if (init_chopsticks(data) != SUCCESS)
		return (ERROR);
	if (init_philos(data) != SUCCESS)
		return (ERROR);
	if (init_data(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
