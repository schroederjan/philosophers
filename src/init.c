/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:15:30 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 20:07:06 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_chopsticks(t_philo *philo, t_chopstick *chopsticks)
{
	int i;

	i = philo->id - 1;
	if (i % 2 == 0)
	{
		philo->left_chopstick = &chopsticks[i];
		philo->right_chopstick = &chopsticks[(i + 1) % philo->data->num_philos];
	}
	else
	{
		philo->left_chopstick = &chopsticks[(i + 1) % philo->data->num_philos];
		philo->right_chopstick = &chopsticks[i];
	}
}

static int init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].has_eaten_enough = false;
		data->philos[i].last_meal_time = 0;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (print_error_and_return(
						"Philosopher mutex initialization failed"));
		assign_chopsticks(&data->philos[i], data->chopsticks);
		i++;
	}
	return SUCCESS;
}

static int init_chopsticks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->chopsticks[i].mutex, NULL) != 0)
			return (print_error_and_return(
						"Chopstick mutex initialization failed"));
		data->chopsticks[i].id = i;
		i++;
	}
	return SUCCESS;
}

static int init_data(t_data *data)
{
	data->simulation_running = false;
	data->time_to_think = data->time_to_die - data->time_to_eat - data->time_to_sleep;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 ||
			pthread_mutex_init(&data->simulation_mutex, NULL) != 0)
		return (print_error_and_return("Global mutex initialization failed"));
	data->simulation_start_time = get_current_time();
	return SUCCESS;
}

int initialize_simulation(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->chopsticks = malloc(sizeof(t_chopstick) * data->num_philos);
	if (!data->philos || !data->chopsticks)
		return (print_error_and_return("Memory allocation failed"));

	if (init_chopsticks(data) != SUCCESS)
		return ERROR;
	if (init_philos(data) != SUCCESS)
		return ERROR;
	if (init_data(data) != SUCCESS)
		return ERROR;
	return SUCCESS;
}
