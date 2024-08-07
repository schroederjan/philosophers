/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:45:26 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/07 22:21:09 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void take_chopsticks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_chopstick->mutex);
	print_status(philo->data, philo->id, "has taken a chopstick");
	pthread_mutex_lock(&philo->right_chopstick->mutex);
	print_status(philo->data, philo->id, "has taken a chopstick");
}

static void release_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_chopstick->mutex);
	pthread_mutex_unlock(&philo->right_chopstick->mutex);
}

static void eat(t_philo *philo)
{
	long start_time;

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);

	print_status(philo->data, philo->id, "is eating");
	start_time = get_current_time();
	while (get_current_time() - start_time < philo->data->time_to_eat)
	{
		if (!is_simulation_running(philo->data))
			return;
		usleep(100);
	}
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long start_time;

	// Stagger start times to prevent deadlock
	if (philo->id % 2 == 0)
		usleep(1000);

	while (is_simulation_running(philo->data))
	{
		print_status(philo->data, philo->id, "is thinking");
		take_chopsticks(philo);
		eat(philo);
		release_chopsticks(philo);
		print_status(philo->data, philo->id, "is sleeping");

		start_time = get_current_time();
		while (get_current_time() - start_time < philo->data->time_to_sleep)
		{
			if (!is_simulation_running(philo->data))
				return NULL;
			usleep(100);
		}
	}
	return NULL;
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	long current_time;
	bool all_full;

	while (is_simulation_running(data))
	{
		all_full = true;
		for (i = 0; i < data->num_philos; i++)
		{
			pthread_mutex_lock(&data->philosophers[i].meal_mutex);
			current_time = get_current_time();
			if (current_time - data->philosophers[i].last_meal_time > data->time_to_die)
			{
				print_status(data, data->philosophers[i].id, "died");
				set_simulation_status(data, false);
				pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
				return NULL;
			}
			if (data->meals_required > 0 && data->philosophers[i].meals_eaten < data->meals_required)
			{
				all_full = false;
			}
			pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
		}
		if (data->meals_required > 0 && all_full)
		{
			set_simulation_status(data, false);
			return NULL;
		}
		usleep(100);
	}
	return NULL;
}

void start_simulation(t_data *data)
{
	int i;
	pthread_t monitor;

	data->start_time = get_current_time();
	set_simulation_status(data, true);

	for (i = 0; i < data->num_philos; i++)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]) != 0)
		{
			// Handle error
			return;
		}
	}

	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		// Handle error
		return;
	}

	// Wait for threads to finish
	pthread_join(monitor, NULL);
	for (i = 0; i < data->num_philos; i++)
	{
		pthread_join(data->philosophers[i].thread, NULL);
	}
}
