/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:45:26 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/12 21:36:50 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philosopher_threads(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->simulation_start_time = get_current_time();
	set_simulation_status(data, true);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, \
					NULL, philosopher_routine, &data->philos[i]) != 0)
		{
			set_simulation_status(data, false);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		set_simulation_status(data, false);
		return ;
	}
	pthread_join(monitor, NULL);
	set_simulation_status(data, false);
	join_philosopher_threads(data);
}
