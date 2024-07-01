/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:53:53 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/01 16:41:52 by adapassa         ###   ########.fr       */
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
	int						id;
	pthread_t				supervisor_id;
	size_t					last_meal;
	pthread_mutex_t			*fork_l;
	pthread_mutex_t 		*fork_r;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	int						meal_num;
	bool					dead_flag;
	int						target_meals;
	struct	s_controller	*controller;
}	t_philo;

typedef struct s_controller
{
	pthread_t			*tid;
	pthread_t			supervisor_id;
	pthread_mutex_t 	*forks;
	bool				dead_flag;
	int					num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					n_times_to_eat;
	uint64_t			start_time;
	t_philo				*philos;
	bool				win_flag;
	bool				exit_flag;
	bool				living_flag;
	bool				stop_he_already_dead;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		lock;
	pthread_mutex_t		timeout_lock;
	pthread_mutex_t		state_lock;
	pthread_mutex_t		ultimate_lock;
}	t_controller;

int			arg_parser(char **av);
int			str_is_digit(const char *str);
int			ft_atoi(const char *str);
int			controller_init(t_controller *elem, char **av);
int			ft_strncmp(char *s1, char *s2, size_t n);
uint64_t	get_time(void);
int			ft_usleep(__useconds_t time);
void		*routine(void *philo_pointer);
int			init_routine(t_controller *controller);
void		distribute_forks(t_controller *controller);
char		*ft_itoa(int n);
int			case_one(t_controller *controller);
void		ft_init_mutex(t_controller *controller);
void		init_forks(t_controller *controller);
void		free_exit(t_controller *controller);
void		free_exit_multi(t_controller *data);
void		init_philos(t_controller *controller);
// Actions
void		philo_die(t_philo *philo);
int			philo_eat(t_philo *philo);
void		philo_print(t_philo *philo, int unlock);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
//void		die_eating(t_philo *philo);
// Controls
int			check_death(t_philo *philo, int nb);
int			eat_time_setter(t_philo *philo);
void		forks_down(t_philo *philo);
void		take_forks(t_philo *philo);
void		distribute_forks(t_controller *controller);
void		*monitoring(void *philo_pointer);

#endif
