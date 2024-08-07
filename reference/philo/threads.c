/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:13:04 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/24 19:26:58 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*die_lonely(void *ptr);

int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->num_philos == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL,
				die_lonely, &data->philos[0]))
			return (ft_return("pthread_create philo failed"));
	}
	else
	{
		while (++i < data->num_philos)
			if (pthread_create(&data->philos[i].thread_id, NULL,
					routine, &data->philos[i]))
				return (ft_return("pthread_create philos failed"));
	}
	if (pthread_create(&data->thread_monitor, NULL, monitor, data))
		return (ft_return("pthread_create monitor failed"));
	change_mutex(&data->all_ready_mutex, &data->all_ready, YES);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	change_mutex(&data->game_over_mutex, &data->game_over, YES);
	pthread_join(data->thread_monitor, NULL);
	return (SUCCESS);
}

static void	*die_lonely(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == NO)
		usleep(200);
	update_last_meal_time(philo);
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->all_ready_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->game_over_mutex);
}
