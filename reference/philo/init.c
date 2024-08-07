/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:11:52 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/28 14:01:08 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks);
static void	init_philos(t_data *data);

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->philos || !data->forks)
		return (ft_return("Malloc failed"));
	if (!data->philos || !data->forks)
		return (ft_return("Malloc Error"));
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->forks[i].fork_id = i;
		i++;
	}
	data->all_ready = NO;
	data->game_over = NO;
	data->time_to_think = data->time_to_die - data->time_to_eat 
		- data->time_to_sleep;
	pthread_mutex_init(&data->all_ready_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->game_over_mutex, NULL);
	init_philos(data);
	data->game_start_time = get_time();
	return (SUCCESS);
}

//init lock for each philo
static void	init_philos(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].is_full = NO;
		data->philos[i].meals = 0;
		data->philos[i].last_meal_time = get_time();
		pthread_mutex_init(&data->philos[i].is_full_mutex, NULL);
		pthread_mutex_init(&data->philos[i].meal_time_mutex, NULL);
		assign_forks(&data->philos[i], data->forks);
		i++;
	}
}

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	int	i;

	i = philo->id;
	if (i % 2 != 0)
	{
		philo->first_f = &forks[i % philo->data->num_philos];
		philo->second_f = &forks[i - 1];
	}
	else
	{
		philo->first_f = &forks[i - 1];
		philo->second_f = &forks[i % philo->data->num_philos];
	}
}
