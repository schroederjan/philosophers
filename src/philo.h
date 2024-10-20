/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:08:31 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/20 17:18:46 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define COLOR_RESET   "\033[0m"
# define COLOR_RED     "\033[0;31m"
# define COLOR_GREEN   "\033[0;32m"
# define COLOR_YELLOW  "\033[0;33m"
# define COLOR_BLUE    "\033[0;34m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_CYAN    "\033[0;36m"
# define COLOR_WHITE   "\033[0;37m"

# define SUCCESS 0
# define ERROR	1

typedef struct s_chopstick
{
	pthread_mutex_t	mutex;
	int				id;
}	t_chopstick;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				meals_required;
	bool			simulation_running;
	long			simulation_start_time;
	t_chopstick		*chopsticks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_barrier_t start_barrier;
}	t_data;

struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	bool			has_eaten_enough;
	pthread_t		thread;
	t_chopstick		*left_chopstick;
	t_chopstick		*right_chopstick;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
};

// Function prototypes
int		parse_arguments(int argc, char **argv, t_data *data);
int		initialize_simulation(t_data *data);
void	start_simulation(t_data *data);
void	*monitor_routine(void *arg);
void	*philosopher_routine(void *arg);
void	cleanup_simulation(t_data *data);

// Utility functions
long	get_current_time(void);
long	atoi_positive_long(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_usleep(long milliseconds);

// Print utility functions
int		print_error(const char *msg, int return_code);
void	print_status(t_data *data, int philo_id, const char *status);
void	print_parse_error_usage(const char *program_name);
void	print_statistics(t_data *data);

// Mutex utility functions
bool	is_simulation_running(t_data *data);
void	set_simulation_status(t_data *data, bool status);
// void	take_chopsticks(t_philo *philo);
bool	take_chopsticks(t_philo *philo);
void	release_chopsticks(t_philo *philo);
void	handle_single_philosopher(t_philo *philo);

#endif
