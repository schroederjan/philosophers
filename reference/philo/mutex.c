/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:12:23 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/21 20:21:34 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_mutex(pthread_mutex_t *lock, int *value, int status)
{
	pthread_mutex_lock(lock);
	*value = status;
	pthread_mutex_unlock(lock);
}

int	check_mutex(pthread_mutex_t *lock, int *value)
{
	int	status;

	pthread_mutex_lock(lock);
	status = *value;
	pthread_mutex_unlock(lock);
	return (status);
}

int	if_game_over(t_data *data)
{
	int	status;

	status = check_mutex(&data->game_over_mutex, &data->game_over);
	return (status);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
}
