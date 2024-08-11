#include "philo.h"

#define TIME_MARGIN 10 // ms

static void take_chopsticks(t_philo *philo)
{
	// Implement global ordering to prevent deadlock
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_chopstick->mutex);
		print_status(philo->data, philo->id, "has taken a chopstick");
		pthread_mutex_lock(&philo->left_chopstick->mutex);
		print_status(philo->data, philo->id, "has taken a chopstick");
	}
	else
	{
		pthread_mutex_lock(&philo->left_chopstick->mutex);
		print_status(philo->data, philo->id, "has taken a chopstick");
		pthread_mutex_lock(&philo->right_chopstick->mutex);
		print_status(philo->data, philo->id, "has taken a chopstick");
	}
}

static void release_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_chopstick->mutex);
	pthread_mutex_unlock(&philo->right_chopstick->mutex);
}

static void eat(t_philo *philo)
{
	long start_time;

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);

	print_status(philo->data, philo->id, "is eating");
	start_time = get_current_time();
	while (get_current_time() - start_time < philo->data->time_to_eat)
	{
		if (!is_simulation_running(philo->data))
			return;
		usleep(1000); // Sleep for 1ms instead of 100us for better precision
	}
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long start_time;

	philo->last_meal_time = philo->data->simulation_start_time;

	if (philo->id % 2 == 0)
		usleep(1000);

	if (philo->data->num_philos == 1)
	{
		print_status(philo->data, philo->id, "has taken a chopstick");
		while (is_simulation_running(philo->data))
			usleep(1000);
		return NULL;
	}

	while (is_simulation_running(philo->data))
	{
		print_status(philo->data, philo->id, "is thinking");
		take_chopsticks(philo);
		eat(philo);
		release_chopsticks(philo);
		print_status(philo->data, philo->id, "is sleeping");

		start_time = get_current_time();
		while (get_current_time() - start_time < philo->data->time_to_sleep)
		{
			if (!is_simulation_running(philo->data))
				return NULL;
			usleep(1000); // Sleep for 1ms instead of 100us
		}
	}
	return NULL;
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	long current_time;
	bool all_full;

	while (is_simulation_running(data))
	{
		all_full = true;
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			current_time = get_current_time();
			if (current_time - data->philos[i].last_meal_time > data->time_to_die + TIME_MARGIN)
			{
				print_status(data, data->philos[i].id, "died");
				set_simulation_status(data, false);
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
				return NULL;
			}
			if (data->meals_required > 0 && data->philos[i].meals_eaten < data->meals_required)
			{
				all_full = false;
			}
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
		if (data->meals_required > 0 && all_full)
		{
			set_simulation_status(data, false);
			return NULL;
		}
		usleep(1000); // Check every 1ms instead of 100us
	}
	return NULL;
}
