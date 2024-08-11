/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:03:31 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 23:43:58 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define TIME_MARGIN 10 // ms

static bool	check_philosopher_death(t_data *data, t_philo *philo)
{
	long current_time;

	current_time = get_current_time();
	if (current_time - philo->last_meal_time > data->time_to_die + TIME_MARGIN)
	{
		print_status(data, philo->id, "died");
		set_simulation_status(data, false);
		return true;
	}
	return false;
}

static bool	check_all_philosophers_full(t_data *data)
{
	int i;
	bool all_full;

	i = 0;
	all_full = true;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (check_philosopher_death(data, &data->philos[i]))
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (false);
		}
		if (data->meals_required > 0 && \
				data->philos[i].meals_eaten < data->meals_required)
			all_full = (false);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (data->meals_required > 0 && all_full)
	{
		set_simulation_status(data, false);
		return (true);
	}
	return (false);
}

void    *monitor_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (is_simulation_running(data))
	{
		if (check_all_philosophers_full(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
