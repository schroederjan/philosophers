/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:23:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/24 19:29:57 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo);
static void	thinking(t_philo *philo);

//print sleep then stop simulation, so visualizer will show full span of eating
void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == NO)
		usleep(200);
	if (philo->id % 2 == 1)
		ft_usleep(1);
	while (if_game_over(philo->data) == NO)
	{
		eating(philo);
		print_msg(philo, SLEEP);
		if (check_mutex(&philo->is_full_mutex, &philo->is_full) == YES)
			return (NULL);
		if (if_game_over(philo->data) == NO)
			ft_usleep(philo->data->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	if (if_game_over(philo->data) == YES)
		return ;
	pthread_mutex_lock(&philo->second_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	update_last_meal_time(philo);
	print_msg(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	pthread_mutex_unlock(&philo->second_f->fork_mutex);
	philo->meals++;
	if (philo->meals == philo->data->meals_must_have)
		change_mutex(&philo->is_full_mutex, &philo->is_full, YES);
}

static void	thinking(t_philo *philo)
{
	print_msg(philo, THINK);
	if (if_game_over(philo->data) == NO)
	{
		if (philo->data->time_to_think > 5)
			ft_usleep(philo->data->time_to_think * 0.8);
	}
}
