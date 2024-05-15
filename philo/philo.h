#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_philo
{
	int	id;
	pthread_t api_data;
	size_t last_meal;
	pthread_mutex_t fork_l;
	pthread_mutex_t fork_r;
	// pthread_mutex_t	*write_lock;
	// pthread_mutex_t	*dead_lock;
	// pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_controller
{
	bool		dead_flag;
	int			num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			n_times_to_eat;
	t_philo		*philos;
	// pthread_mutex_t	dead_lock;
	// pthread_mutex_t	meal_lock;
	// pthread_mutex_t	write_lock;
}	t_controller;

int		arg_parser(char **av);
int		str_is_digit(const char *str);
int		ft_atoi(const char *str);
int		controller_init(t_controller *elem, char **av);
int		ft_strncmp(char *s1, char *s2, size_t n);
// void	init_philo(t_controller *controller);

#endif
