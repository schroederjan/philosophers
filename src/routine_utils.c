/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:51 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/20 17:18:30 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool take_chopsticks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_chopstick->mutex);
        if (!is_simulation_running(philo->data))
        {
            pthread_mutex_unlock(&philo->right_chopstick->mutex);
            return false;
        }
        print_status(philo->data, philo->id, "has taken a chopstick");
        
        pthread_mutex_lock(&philo->left_chopstick->mutex);
        if (!is_simulation_running(philo->data))
        {
            pthread_mutex_unlock(&philo->right_chopstick->mutex);
            pthread_mutex_unlock(&philo->left_chopstick->mutex);
            return false;
        }
        print_status(philo->data, philo->id, "has taken a chopstick");
    }
    else
    {
        pthread_mutex_lock(&philo->left_chopstick->mutex);
        if (!is_simulation_running(philo->data))
        {
            pthread_mutex_unlock(&philo->left_chopstick->mutex);
            return false;
        }
        print_status(philo->data, philo->id, "has taken a chopstick");
        
        pthread_mutex_lock(&philo->right_chopstick->mutex);
        if (!is_simulation_running(philo->data))
        {
            pthread_mutex_unlock(&philo->left_chopstick->mutex);
            pthread_mutex_unlock(&philo->right_chopstick->mutex);
            return false;
        }
        print_status(philo->data, philo->id, "has taken a chopstick");
    }
    return true;
}

void	release_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_chopstick->mutex);
	pthread_mutex_unlock(&philo->right_chopstick->mutex);
}

void	handle_single_philosopher(t_philo *philo)
{
	print_status(philo->data, philo->id, "has taken a chopstick");
	while (is_simulation_running(philo->data))
		ft_usleep(100);
}
