/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:05 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/24 08:40:04 by adapassa         ###   ########.fr       */
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
	// while (++i < data->num_of_philos)
	// {
	// 	pthread_mutex_destroy(&data->forks[i]);
	// 	//pthread_mutex_destroy(data->philos[i].fork_l);
	// 	//pthread_mutex_destroy(data->philos[i].fork_r);

	// }
	// while (i < data->num_of_philos)
	// {
	// 	free(data->tid[i]);
	// 	//free(data->philos[i]);
	// 	//pthread_mutex_destroy(&controller->forks[i]);
	// 	i++;
	// }
	// while (i < data->num_of_philos)
	// {
	// 	//pthread_detach(data->tid[i]);
	// 	//pthread_detach(controller->tid[j]);
	// 	i++;
	// }
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->lock);
	//clear_data(data);
	exit(0);
}