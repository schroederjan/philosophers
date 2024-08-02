#include "philo.h"

// Function prototypes
static int handle_arguments(int argc, char **argv, t_data *data);

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 5 && argc != 6)
	{
		print_error(\
				"Usage: ./philo \
				number_of_philosophers \
				time_to_die time_to_eat \
				time_to_sleep [number_of_meals]\n", \
				EXIT_FAILURE);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (print_error("Memory allocation failed", EXIT_FAILURE));
	if (handle_arguments(argc, argv, data) == EXIT_FAILURE)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (init_data(data) == EXIT_FAILURE)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (start_threads(data) == EXIT_FAILURE)
	{
		free(data->philos);
		free(data->chopsticks);
		free(data);
		return (EXIT_FAILURE);
	}
	print_meals(data);
	destroy_mutexes(data);
	free(data->philos);
	free(data->forks);
	free(data);
	return (EXIT_SUCCESS);
}

// Function to handle input arguments and initialize the data structure
static int handle_arguments(int argc, char **argv, t_data *data) {
	// Validate and parse input arguments
	if (check_input(argv) == EXIT_FAILURE) {
		return (print_error("Input validation failed", EXIT_FAILURE));
	}

	if (parse_input(data, argv) == EXIT_FAILURE) {
		return (print_error("Input parsing failed", EXIT_FAILURE));
	}

	return (EXIT_SUCCESS);
}

