/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:13:16 by xiwang            #+#    #+#             */
/*   Updated: 2024/08/07 20:55:30 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_return(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	print_msg(t_philo *philo, char *s)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->game_start_time;
	if (if_game_over(philo->data) == NO)
	{
		if (ft_strncmp(EAT, s, 9) == 0)
			printf(E"%ld %d %s\n"RST, time, philo->id, s);
		else
			printf(T"%ld %d %s\n"RST, time, philo->id, s);
	}
	else if (ft_strncmp(DIE, s, 5) == 0)
		printf(D"%ld %d %s\n"RST, time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
