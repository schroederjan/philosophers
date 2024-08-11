/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:25:07 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 21:39:27 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_error_and_return(const char *error_message)
{
	printf(COLOR_RED "Error: %s\n" COLOR_RESET, error_message);
	return 1;
}

long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2 || !*s1 || !*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

const char* get_color_for_status(const char *status) {
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

void print_status(t_data *data, int philo_id, const char *status)
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
