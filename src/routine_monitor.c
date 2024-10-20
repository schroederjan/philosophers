/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:03:31 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/20 17:13:52 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static bool	check_philosopher_death(t_data *data, t_philo *philo) */
/* { */
/*     long	current_time; */
/*  */
/*     current_time = get_current_time(); */
/*     if (current_time - philo->last_meal_time > data->time_to_die) */
/*     { */
/*         print_status(data, philo->id, "died"); */
/*         set_simulation_status(data, false); */
/*         return (true); */
/*     } */
/*     return (false); */
/* } */
/*  */
/* static bool	check_all_philosophers_full(t_data *data) */
/* { */
/*     int		i; */
/*     bool	all_full; */
/*  */
/*     i = 0; */
/*     all_full = true; */
/*     while (i < data->num_philos) */
/*     { */
/*         pthread_mutex_lock(&data->philos[i].meal_mutex); */
/*         if (check_philosopher_death(data, &data->philos[i])) */
/*         { */
/*             pthread_mutex_unlock(&data->philos[i].meal_mutex); */
/*             return (true); */
/*         } */
/*         if (data->meals_required > 0 && \ */
/*                 data->philos[i].meals_eaten < data->meals_required) */
/*             all_full = (false); */
/*         pthread_mutex_unlock(&data->philos[i].meal_mutex); */
/*         i++; */
/*     } */
/*     if (data->meals_required > 0 && all_full) */
/*     { */
/*         set_simulation_status(data, false); */
/*         return (true); */
/*     } */
/*     return (false); */
/* } */
/*  */
/* void	*monitor_routine(void *arg) */
/* { */
/*     t_data	*data; */
/*  */
/*     data = (t_data *)arg; */
/*     while (is_simulation_running(data)) */
/*     { */
/*         if (check_all_philosophers_full(data)) */
/*             return (NULL); */
/*     } */
/*     return (NULL); */
/* } */


void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long current_time;

    pthread_barrier_wait(&data->start_barrier);
    while (is_simulation_running(data))
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            current_time = get_current_time();
            if (current_time - data->philos[i].last_meal_time > data->time_to_die)
            {
                print_status(data, data->philos[i].id, "died");
                set_simulation_status(data, false);
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->philos[i].meal_mutex);

            if (data->meals_required > 0 && 
                data->philos[i].meals_eaten >= data->meals_required)
            {
                data->philos[i].has_eaten_enough = true;
            }

            i++;
        }

        // Check if all philosophers have eaten enough
        if (data->meals_required > 0)
        {
            bool all_full = true;
            for (i = 0; i < data->num_philos; i++)
            {
                if (!data->philos[i].has_eaten_enough)
                {
                    all_full = false;
                    break;
                }
            }
            if (all_full)
            {
                set_simulation_status(data, false);
                return NULL;
            }
        }

        usleep(1000); // Short sleep to prevent busy-waiting
    }

    return NULL;
}
