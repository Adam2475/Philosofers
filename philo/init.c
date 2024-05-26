/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:30:44 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/26 20:40:48 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(__useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	controller_init(t_controller *elem, char **av)
{
	elem->num_of_philos = ft_atoi(av[1]);
	elem->time_to_die = (size_t)ft_atoi(av[2]);
	elem->time_to_eat = (size_t)ft_atoi(av[3]);
	elem->time_to_sleep = (size_t)ft_atoi(av[4]);
	elem->dead_flag = false;
	elem->start_time = get_time();
	if (av[5])
		elem->n_times_to_eat = ft_atoi(av[5]);
	else
		elem->n_times_to_eat = -1;
	if (elem->time_to_die < 1 || elem->time_to_sleep < 1
		|| elem->time_to_eat < 1)
		return (1);
	return (0);
}

int	init_routine(t_controller *controller)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < controller->num_of_philos)
	{
		if (pthread_create(&controller->tid[i], NULL, &routine, &controller->philos[i]) != 0)
		{
			printf("error in initializing routine!\n");
			return (1);
		}
		//controller->philos[i].controller->start_time = controller->start_time;
		//controller->philos[i].last_meal = controller->start_time;
		//printf("%lu\n", controller->philos[i].last_meal);
		//printf("%lu\n", controller->philos[i].controller->start_time);
		i++;
	}
	j = i;
	while (j > 0)
	{
		j--;
		ft_usleep(1);
		pthread_join(controller->tid[j], NULL);
	}
	return (0);
}

void	ft_init_mutex(t_controller *controller)
{
	int	i;

	i = 0;
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
