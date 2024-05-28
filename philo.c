#include "philo.h"

long current_timestamp(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000 + 
			(current_time.tv_usec - start_time.tv_usec) / 1000);
}

void print_status(t_philosopher *philosopher, char *status)
{
	pthread_mutex_lock(philosopher->print_lock);
	printf("%ld %d %s\n", current_timestamp(philosopher->start_time), \
			philosopher->id, status);
	pthread_mutex_unlock(philosopher->print_lock);
}

void think(t_philosopher *philosopher)
{
	print_status(philosopher, "is thinking");
}

void eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_status(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->right_fork);
	print_status(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->meal_lock);
	philosopher->last_meal_time = current_timestamp(philosopher->start_time);
	philosopher->meals_eaten++;
	pthread_mutex_unlock(philosopher->meal_lock);
	print_status(philosopher, "is eating");
	usleep(philosopher->time_to_eat * 1000);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

void sleep_philo(t_philosopher *philosopher)
{
	print_status(philosopher, "is sleeping");
	usleep(philosopher->time_to_sleep * 1000);
}

void *philosopher_routine(void *arg)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)arg;
	while (1) 
	{
		think(philosopher);
		eat(philosopher);
		sleep_philo(philosopher);
	}
	return (NULL);
}

int allocate_memory( \
		int num_of_philosophers, pthread_t **threads, \
		pthread_mutex_t **forks, t_philosopher **philosophers)
{
	*threads = malloc(sizeof(pthread_t) * num_of_philosophers);
	*forks = malloc(sizeof(pthread_mutex_t) * num_of_philosophers);
	*philosophers = malloc(sizeof(t_philosopher) * num_of_philosophers);

	if (!(*threads) || !(*forks) || !(*philosophers)) {
		perror("Failed to allocate memory");
		return 1;
	}

	return 0;
}

void initialize_forks(int num_of_philosophers, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < num_of_philosophers) {
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void initialize_philosophers(int num_of_philosophers, t_philosopher *philosophers, pthread_mutex_t *forks, pthread_mutex_t *print_lock, pthread_mutex_t *meal_lock, long time_to_die, long time_to_eat, long time_to_sleep, int meals_needed)
{
	int i;
	struct timeval start_time;

	i = 0;
	gettimeofday(&start_time, NULL);
	while (i < num_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].num_of_philosophers = num_of_philosophers;
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].meals_needed = meals_needed;
		philosophers[i].meals_eaten = 0;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_of_philosophers];
		philosophers[i].print_lock = print_lock;
		philosophers[i].meal_lock = meal_lock;
		philosophers[i].last_meal_time = 0;
		philosophers[i].start_time = start_time;
		i++;
	}
}

void create_philosopher_threads(int num_of_philosophers, pthread_t *threads, t_philosopher *philosophers)
{
	int i;

	i = 0;
	while (i < num_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
}

void join_philosopher_threads(int num_of_philosophers, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < num_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void destroy_mutexes(int num_of_philosophers, pthread_mutex_t *forks, pthread_mutex_t *print_lock, pthread_mutex_t *meal_lock) {
	int i;

	i = 0;
	while (i < num_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(print_lock);
	pthread_mutex_destroy(meal_lock);
}

void free_memory(pthread_t *threads, pthread_mutex_t *forks, t_philosopher *philosophers)
{
	free(threads);
	free(forks);
	free(philosophers);
}

void initialize_variables(int argc, char **argv, int *num_of_philosophers, long *time_to_die, long *time_to_eat, long *time_to_sleep, int *meals_needed)
{
	*num_of_philosophers = atoi(argv[1]);
	*time_to_die = atol(argv[2]);
	*time_to_eat = atol(argv[3]);
	*time_to_sleep = atol(argv[4]);
	if (argc == 6)
		*meals_needed = atoi(argv[5]);
	else
		*meals_needed = -1;
}

int validate_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int num_of_philosophers;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int meals_needed;
	pthread_t *threads;
	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
	pthread_mutex_t meal_lock;
	t_philosopher *philosophers;

	if (validate_arguments(argc, argv) != 0)
        return (1);
	initialize_variables(argc, argv, &num_of_philosophers, &time_to_die, &time_to_eat, &time_to_sleep, &meals_needed);
	if (allocate_memory(num_of_philosophers, &threads, &forks, &philosophers))
		return (1);
	initialize_forks(num_of_philosophers, forks);
	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&meal_lock, NULL);
	initialize_philosophers(num_of_philosophers, philosophers, forks, &print_lock, &meal_lock, time_to_die, time_to_eat, time_to_sleep, meals_needed);
	create_philosopher_threads(num_of_philosophers, threads, philosophers);
	join_philosopher_threads(num_of_philosophers, threads);
	destroy_mutexes(num_of_philosophers, forks, &print_lock, &meal_lock);
	free_memory(threads, forks, philosophers);
	return (0);
}

