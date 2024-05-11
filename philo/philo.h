#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_philo
{
	int	i;

}	t_philo;

typedef struct s_controller
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_to_eat;
}	t_controller;

int arg_parser(char **av);
int str_is_digit(const char *str);
int	ft_atoi(const char *str);

#endif
