/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:25:07 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/07 22:21:23 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void print_status(t_data *data, int philo_id, const char *status)
{
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_running(data))
	{
		printf("%ld %d %s\n", get_current_time() - data->start_time, philo_id, status);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

int safe_sleep(long duration)
{
	long start_time = get_current_time();
	while (get_current_time() - start_time < duration)
	{
		usleep(100);
	}
	return 0;
}

bool is_simulation_running(t_data *data)
{
	bool status;
	pthread_mutex_lock(&data->simulation_mutex);
	status = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_mutex);
	return status;
}

void set_simulation_status(t_data *data, bool status)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = status;
	pthread_mutex_unlock(&data->simulation_mutex);
}
