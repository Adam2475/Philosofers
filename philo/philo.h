/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:53:53 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/20 19:45:11 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>
#include <limits.h>

typedef struct s_philo
{
	int					id;
	pthread_t			api_data;
	size_t				last_meal;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t 	*fork_r;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	bool				dead_flag;
	int					meals_num;
	int					target_meals;
	// t_controller	*controller;
	struct	s_controller	*controller;
}	t_philo;

typedef struct s_controller
{
	pthread_t		*tid;
	pthread_mutex_t *forks;
	bool			dead_flag;
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				n_times_to_eat;
	uint64_t		start_time;
	t_philo			*philos;
	// pthread_mutex_t	*write_lock;
	// pthread_mutex_t	*dead_lock;
	// pthread_mutex_t	*meal_lock;
}	t_controller;

int			arg_parser(char **av);
int			str_is_digit(const char *str);
int			ft_atoi(const char *str);
int			controller_init(t_controller *elem, char **av);
int			ft_strncmp(char *s1, char *s2, size_t n);
uint64_t	get_time(void);
int			ft_usleep(__useconds_t time);
void		*routine(void *philo_pointer);
void		init_multiple(t_controller *controller);
int			init_routine(t_controller *controller);
void		distribute_forks(t_controller *controller);
char		*ft_itoa(int n);
// Actions
void		philo_die(t_philo *philo);

#endif
