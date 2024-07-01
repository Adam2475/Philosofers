/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:05 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/01 14:41:47 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->fork_l < philo->fork_r)
	{
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(philo->fork_r);
	} 
	else 
	{
		pthread_mutex_lock(philo->fork_r);
		pthread_mutex_lock(philo->fork_l);
	}
}

void	forks_down(t_philo *philo)
{
	if (philo->fork_l < philo->fork_r)
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	} 
	else 
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
	}
}

void	free_exit_multi(t_controller *data)
{
	int	i;

	i = -1;
	if (data->philos)
		free(data->philos);
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->forks);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->ultimate_lock);
	exit(0);
}

void	distribute_forks(t_controller *controller)
{
	int	i;

	i = 0;
	while (i < controller->num_of_philos)
	{
		if (i == 0)
			controller->philos[i].fork_r = &controller->forks[controller->num_of_philos - 1];
		else
			controller->philos[i].fork_r = &controller->forks[i - 1];

		controller->philos[i].fork_l = &controller->forks[i];
		i++;
	}
	init_routine(controller);
}