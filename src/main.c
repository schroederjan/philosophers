#include "philo.h"

int main(int argc, char **argv)
{
	t_data data;

	if (parse_arguments(argc, argv, &data) != 0)
	{
		printf("Error: Invalid arguments\n");
		return 1;
	}

	if (initialize_simulation(&data) != 0)
	{
		printf("Error: Failed to initialize simulation\n");
		return 1;
	}

	start_simulation(&data);

	cleanup_simulation(&data);

	return 0;
}

int parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return 1;

	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->meals_required = (argc == 6) ? atoi(argv[5]) : -1;

	if (data->num_philos < 1 || data->num_philos > 200 ||
			data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60 ||
			(argc == 6 && data->meals_required < 1))
		return 1;

	return 0;
}

int initialize_simulation(t_data *data)
{
	int i;

	data->chopsticks = malloc(sizeof(t_chopstick) * data->num_philos);
	data->philosophers = malloc(sizeof(t_philo) * data->num_philos);

	if (!data->chopsticks || !data->philosophers)
		return 1;

	for (i = 0; i < data->num_philos; i++)
	{
		pthread_mutex_init(&data->chopsticks[i].mutex, NULL);
		data->chopsticks[i].id = i;

		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_time = 0;  // Will be set when simulation starts
		data->philosophers[i].left_chopstick = &data->chopsticks[i];
		data->philosophers[i].right_chopstick = &data->chopsticks[(i + 1) % data->num_philos];
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL);
	}

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);

	return 0;
}

void cleanup_simulation(t_data *data)
{
	int i;

	for (i = 0; i < data->num_philos; i++)
	{
		pthread_mutex_destroy(&data->chopsticks[i].mutex);
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
	}

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->simulation_mutex);

	free(data->chopsticks);
	free(data->philosophers);
}
