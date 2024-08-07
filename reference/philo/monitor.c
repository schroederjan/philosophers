/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:12:13 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/23 18:28:01 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_one_dies(t_philo *philo)
{
	long	time;
	long	starving;

	if (check_mutex(&philo->is_full_mutex, &philo->is_full) == YES)
		return (NO);
	starving = philo->data->time_to_die;
	pthread_mutex_lock(&philo->meal_time_mutex);
	time = get_time() - philo->last_meal_time;
	if (time >= starving)
	{
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (YES);
	}
	pthread_mutex_unlock(&philo->meal_time_mutex);
	return (NO);
}

void	*monitor(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	while (if_game_over(data) == NO)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (if_one_dies(&data->philos[i]) == YES)
			{
				change_mutex(&data->game_over_mutex, &data->game_over, YES);
				print_msg(&data->philos[i], DIE);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
