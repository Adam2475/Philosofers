/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:05 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/03 19:32:22 by adapassa         ###   ########.fr       */
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
	if (philo->fork_l < philo->fork_r) {
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	} 
	else 
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
	}
}