/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:50:03 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/13 09:36:23 by jschroed         ###   ########.fr       */
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
	long	start_time;
	bool	meal_completed;

	meal_completed = false;
	take_chopsticks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo->data, philo->id, "is eating");
	start_time = get_current_time();
	while (get_current_time() - start_time < philo->data->time_to_eat)
	{
		if (!is_simulation_running(philo->data))
		{
			release_chopsticks(philo);
			return ;
		}
	}
	meal_completed = true;
	release_chopsticks(philo);
	if (meal_completed)
		increment_meal_count(philo);
}

static void	philo_sleep(t_philo *philo)
{
	long	start_time;

	print_status(philo->data, philo->id, "is sleeping");
	start_time = get_current_time();
	while (get_current_time() - start_time < philo->data->time_to_sleep)
	{
		if (!is_simulation_running(philo->data))
			return ;
	}
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
		usleep(150);
	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	while (is_simulation_running(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
