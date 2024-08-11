/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:25:07 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 20:08:24 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_error_and_return(const char *error_message)
{
	printf("Error: %s\n", error_message);
	return 1;
}

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
		printf("%ld %d %s\n", \
				get_current_time() - data->simulation_start_time, \
				philo_id, \
				status);
	pthread_mutex_unlock(&data->print_mutex);
}

long atoi_positive_long(const char *str)
{
	long result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int safe_sleep(long duration)
{
	long simulation_start_time;

	simulation_start_time = get_current_time();
	while (get_current_time() - simulation_start_time < duration)
		usleep(500);
	return (0);
}
