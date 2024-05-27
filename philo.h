#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher {
    int id;
    int num_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int meals_needed;
    int meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long last_meal_time;
    pthread_mutex_t *print_lock;
    pthread_mutex_t *meal_lock;
    struct timeval start_time;
} t_philosopher;

void *philosopher_routine(void *arg);
void think(t_philosopher *philosopher);
void eat(t_philosopher *philosopher);
void sleep_philo(t_philosopher *philosopher);
long current_timestamp(struct timeval start_time);
void print_status(t_philosopher *philosopher, char *status);

#endif
