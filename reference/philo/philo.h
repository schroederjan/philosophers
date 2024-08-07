/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:12:35 by xiwang            #+#    #+#             */
/*   Updated: 2024/08/07 20:55:53 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <unistd.h>//usleep

#define TAKE_FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"

#define RST    "\033[0m"
#define D	   "\033[1;31m"
#define E      "\033[1;32m"
#define T      "\033[1;34m"

#define ERROR -1
#define SUCCESS 0
#define PHILO_MAX 200
#define YES 42
#define NO 24

typedef struct s_data	t_data;

typedef struct s_forks
{
	pthread_mutex_t	fork_mutex;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				is_full;
	int				meals;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*first_f;
	t_fork			*second_f;
	t_data			*data;
	pthread_mutex_t	is_full_mutex;
	pthread_mutex_t	meal_time_mutex;
}	t_philo;

struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				meals_must_have;
	int				all_ready;
	long			game_start_time;
	int				game_over;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		thread_monitor;
	pthread_mutex_t	all_ready_mutex;
	pthread_mutex_t	game_over_mutex;
	pthread_mutex_t	print_mutex;
};

//input
int		check_input(char **av);
int		parse_input(t_data *data, char **av);
//utils
int		ft_return(char *s);
void	print_msg(t_philo *philo, char *s);
long	get_time(void);
int		ft_usleep(size_t milliseconds);
// init
int		init_data(t_data *data);
//mutex
void	change_mutex(pthread_mutex_t *lock, int *value, int status);
int		check_mutex(pthread_mutex_t *lock, int *value);
int		if_game_over(t_data *data);
void	update_last_meal_time(t_philo *philo);
// threads
int		start_threads(t_data *data);
void	destroy_mutexes(t_data *data);
//monitor
void	*monitor(void *ptr);
//routine
void	*routine(void *ptr);
