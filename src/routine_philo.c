/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:50:03 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/22 20:59:29 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	philo_eat(t_philo *philo)
{
	bool	meal_completed;

	meal_completed = false;
	take_chopsticks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo->data, philo->id, "is eating");
	ft_usleep(philo->data->time_to_eat);
	meal_completed = true;
	release_chopsticks(philo);
	if (meal_completed)
		increment_meal_count(philo);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo->data, philo->id, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = philo->data->simulation_start_time;
	if (philo->id % 2 == 0)
		ft_usleep(150);
	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	while (is_simulation_running(philo->data))
	{
		philo_eat(philo);
		if (!is_simulation_running(philo->data)) break;
		philo_sleep(philo);
		if (!is_simulation_running(philo->data)) break;
		philo_think(philo);
		usleep(200);

	}
	return (NULL);
}
