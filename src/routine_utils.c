/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:51 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/14 08:44:33 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_chopsticks(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_chopstick->mutex);
    print_status(philo->data, philo->id, "has taken a chopstick");
    pthread_mutex_lock(&philo->right_chopstick->mutex);
    print_status(philo->data, philo->id, "has taken a chopstick");
}
/* void	take_chopsticks(t_philo *philo) */
/* { */
/*     if (philo->id % 2 == 0) */
/*     { */
/*         pthread_mutex_lock(&philo->right_chopstick->mutex); */
/*         print_status(philo->data, philo->id, "has taken a chopstick"); */
/*         pthread_mutex_lock(&philo->left_chopstick->mutex); */
/*         print_status(philo->data, philo->id, "has taken a chopstick"); */
/*     } */
/*     else */
/*     { */
/*         pthread_mutex_lock(&philo->left_chopstick->mutex); */
/*         print_status(philo->data, philo->id, "has taken a chopstick"); */
/*         pthread_mutex_lock(&philo->right_chopstick->mutex); */
/*         print_status(philo->data, philo->id, "has taken a chopstick"); */
/*     } */
/* } */

void	release_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_chopstick->mutex);
	pthread_mutex_unlock(&philo->right_chopstick->mutex);
}

void	handle_single_philosopher(t_philo *philo)
{
	print_status(philo->data, philo->id, "has taken a chopstick");
	while (is_simulation_running(philo->data))
		usleep(100);
}
