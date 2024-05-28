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

int allocate_memory(int num_of_philosophers, pthread_t **threads, pthread_mutex_t **forks, t_philosopher **philosophers);
void initialize_forks(int num_of_philosophers, pthread_mutex_t *forks);
void initialize_philosophers(int num_of_philosophers, t_philosopher *philosophers, pthread_mutex_t *forks, pthread_mutex_t *print_lock, pthread_mutex_t *meal_lock, long time_to_die, long time_to_eat, long time_to_sleep, int meals_needed);
void create_philosopher_threads(int num_of_philosophers, pthread_t *threads, t_philosopher *philosophers);
void join_philosopher_threads(int num_of_philosophers, pthread_t *threads);
void destroy_mutexes(int num_of_philosophers, pthread_mutex_t *forks, pthread_mutex_t *print_lock, pthread_mutex_t *meal_lock);
void free_memory(pthread_t *threads, pthread_mutex_t *forks, t_philosopher *philosophers);
int validate_arguments(int argc, char **argv);
void initialize_variables(int argc, char **argv, int *num_of_philosophers, long *time_to_die, long *time_to_eat, long *time_to_sleep, int *meals_needed);

#endif
