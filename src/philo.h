/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:08:31 by jschroed          #+#    #+#             */
/*   Updated: 2024/08/11 21:10:55 by jschroed         ###   ########.fr       */
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

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_WHITE   "\033[0;37m"

#define MAX_PHILOSOPHERS 200
#define SUCCESS 0
#define ERROR	1

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
	long			time_to_think;
    int             meals_required;
    bool            simulation_running;
    long            simulation_start_time;
    t_chopstick     *chopsticks;
    t_philo         *philos;
    pthread_mutex_t print_mutex;
    pthread_mutex_t simulation_mutex;
} t_data;

struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
	bool			has_eaten_enough;
    pthread_t       thread;
    t_chopstick     *left_chopstick;
    t_chopstick     *right_chopstick;
    t_data          *data;
    pthread_mutex_t meal_mutex;
};

// Function prototypes
int     parse_arguments(int argc, char **argv, t_data *data);
int     initialize_simulation(t_data *data);
void    start_simulation(t_data *data);
void    *philosopher_routine(void *arg);
void    *monitor_routine(void *arg);
void    cleanup_simulation(t_data *data);

// Utility functions
int		print_error_and_return(const char *error_message);
long    get_current_time(void);
void    print_status(t_data *data, int philo_id, const char *status);
long	atoi_positive_long(const char *str);
int     safe_sleep(long duration);

bool    is_simulation_running(t_data *data);
void    set_simulation_status(t_data *data, bool status);

#endif
