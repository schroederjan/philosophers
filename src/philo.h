/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:08:31 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/02 16:44:00 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PHILOSOPHERS 200

typedef struct s_chopstick
{
	pthread_mutex_t mutex;
	int             id;
} t_chopstick;

typedef struct s_philo t_philo;

typedef struct s_data
{
	int             num_philos;
	long            time_to_die;
	long            time_to_eat;
	long            time_to_sleep;
	int             meals_required;
	bool            simulation_running;
	long            start_time;
	t_chopstick     *chopsticks;
	t_philo         *philosophers;
	pthread_mutex_t print_mutex;
	pthread_mutex_t simulation_mutex;
} t_data;

struct s_philo
{
	int             id;
	int             meals_eaten;
	long            last_meal_time;
	pthread_t       thread;
	t_chopstick     *left_chopstick;
	t_chopstick     *right_chopstick;
	t_data          *data;
	pthread_mutex_t meal_mutex;
};

// Function prototypes
int		parse_arguments(int argc, char **argv, t_data *data);
int     initialize_simulation(t_data *data);
void    start_simulation(t_data *data);
void    *philosopher_routine(void *arg);
void    *monitor_routine(void *arg);
void    cleanup_simulation(t_data *data);

// Utility functions
long    get_current_time(void);
void    print_status(t_data *data, int philo_id, const char *status);
int     safe_sleep(long duration);
bool    is_simulation_running(t_data *data);
void    set_simulation_status(t_data *data, bool status);

#endif
