/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:30:44 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/25 10:35:27 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_controller *controller)
{
	int	i;
	controller->philos = (t_philo *)malloc(sizeof(t_philo) * controller->num_of_philos);
	controller->tid = (pthread_t *)malloc(sizeof(pthread_t) * controller->num_of_philos);

	i = 0;
	init_forks(controller);
	while (i < controller->num_of_philos)
	{
		controller->philos[i].time_to_die = controller->time_to_die;
		controller->philos[i].time_to_eat = controller->time_to_eat;
		controller->philos[i].time_to_sleep = controller->time_to_sleep;
		controller->philos[i].dead_flag = false;
		controller->philos[i].target_meals = controller->n_times_to_eat;
		controller->philos[i].id = i + 1;
		controller->philos[i].controller = controller;
		controller->philos[i].last_meal = controller->start_time;
		controller->philos[i].meal_num = 0;
		controller->philos[i].controller->exit_flag = false;
		i++;
	}
	distribute_forks(controller);
}

int	controller_init(t_controller *elem, char **av)
{
	elem->num_of_philos = ft_atoi(av[1]);
	elem->time_to_die = (size_t)ft_atoi(av[2]);
	elem->time_to_eat = (size_t)ft_atoi(av[3]);
	elem->time_to_sleep = (size_t)ft_atoi(av[4]);
	elem->dead_flag = false;
	elem->living_flag = false;
	elem->win_flag = false;
	elem->start_time = get_time();
	elem->stop_he_already_dead = false;
	if (av[5])
		elem->n_times_to_eat = ft_atoi(av[5]);
	else
		elem->n_times_to_eat = -1;
	if (elem->time_to_die < 1 || elem->time_to_sleep < 1
		|| elem->time_to_eat < 1)
		return (1);
	return (0);
}


void	ft_init_mutex(t_controller *controller)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&controller->write_lock, NULL) != 0)
		exit(1);
	if (pthread_mutex_init(&controller->dead_lock, NULL) != 0)
		exit(1);
	if (pthread_mutex_init(&controller->lock, NULL) != 0)
		exit(1);
	if (pthread_mutex_init(&controller->meal_lock, NULL) != 0)
		exit(1);
	if (pthread_mutex_init(&controller->ultimate_lock, NULL) != 0)
		exit(1);
	while (i < controller->num_of_philos)
	{
		if (pthread_mutex_init(&controller->forks[i], NULL) != 0)
		{
			printf("error initializing forks!\n");
			exit(1);
		}
		i++;
	}
}

void	init_forks(t_controller *controller)
{
	controller->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * controller->num_of_philos);
	ft_init_mutex(controller);
}
