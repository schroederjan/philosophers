/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:05:18 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 22:52:48 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_running(t_data *data)
{
	bool status;

	pthread_mutex_lock(&data->simulation_mutex);
	status = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (status);
}

void	set_simulation_status(t_data *data, bool status)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = status;
	pthread_mutex_unlock(&data->simulation_mutex);
}
