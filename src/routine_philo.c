/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:50:03 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/20 17:19:06 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

bool ft_usleep_check(long milliseconds, t_data *data)
{
    long start_time = get_current_time();
    while ((get_current_time() - start_time) < milliseconds)
    {
        if (!is_simulation_running(data))
            return false;
        usleep(500);
    }
    return true;
}

bool philo_eat(t_philo *philo)
{
    if (!take_chopsticks(philo))
        return false;

    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->meal_mutex);

    print_status(philo->data, philo->id, "is eating");
    if (!ft_usleep_check(philo->data->time_to_eat, philo->data))
    {
        release_chopsticks(philo);
        return false;
    }

    release_chopsticks(philo);
    increment_meal_count(philo);
    return true;
}


bool philo_sleep(t_philo *philo)
{
    print_status(philo->data, philo->id, "is sleeping");
    return ft_usleep_check(philo->data->time_to_sleep, philo->data);
}

bool philo_think(t_philo *philo)
{
    print_status(philo->data, philo->id, "is thinking");
    return is_simulation_running(philo->data);
}

/* static void	philo_eat(t_philo *philo) */
/* { */
/*     bool	meal_completed; */
/*  */
/*     meal_completed = false; */
/*     take_chopsticks(philo); */
/*     pthread_mutex_lock(&philo->meal_mutex); */
/*     philo->last_meal_time = get_current_time(); */
/*     pthread_mutex_unlock(&philo->meal_mutex); */
/*     print_status(philo->data, philo->id, "is eating"); */
/*     ft_usleep(philo->data->time_to_eat); */
/*     meal_completed = true; */
/*     release_chopsticks(philo); */
/*     if (meal_completed) */
/*         increment_meal_count(philo); */
/* } */
/*  */
/* static void	philo_sleep(t_philo *philo) */
/* { */
/*     print_status(philo->data, philo->id, "is sleeping"); */
/*     ft_usleep(philo->data->time_to_sleep); */
/* } */
/*  */
/* void	philo_think(t_philo *philo) */
/* { */
/*     print_status(philo->data, philo->id, "is thinking"); */
/* } */

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;

	pthread_barrier_wait(&philo->data->start_barrier);

	philo->last_meal_time = philo->data->simulation_start_time;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);

	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	while (is_simulation_running(philo->data))
	{
		if (!philo_eat(philo))
			break;
		if (!philo_sleep(philo))
			break;
		if (!philo_think(philo))
			break;
	}
	return NULL;
	/* while (is_simulation_running(philo->data)) */
	/* { */
	/*     philo_eat(philo); */
	/*     philo_sleep(philo); */
	/*     philo_think(philo); */
	/* } */
	/* return (NULL); */
}
