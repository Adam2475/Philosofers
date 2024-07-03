/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:38:09 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/03 14:02:48 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->controller->dead_lock);
	if (philo->controller->dead_flag == 0)
	{
		pthread_mutex_unlock(&philo->controller->dead_lock);
		philo_sleep(philo);
	}
	else
		pthread_mutex_unlock(&philo->controller->dead_lock);
}

void	philo_think_action(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(&philo->controller->dead_lock);
	tmp = philo->controller->dead_flag;
	pthread_mutex_unlock(&philo->controller->dead_lock);
	if (tmp == 0)
		philo_think(philo);
}

int	check_break(t_philo *philo)
{
	pthread_mutex_lock(&philo->controller->state_lock);
	if (philo->controller->exit_flag > 0)
	{
		pthread_mutex_unlock(&philo->controller->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->controller->state_lock);
	pthread_mutex_lock(&philo->controller->dead_lock);
	if (philo->controller->dead_flag > 0)
	{
		pthread_mutex_unlock(&philo->controller->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->controller->dead_lock);
	pthread_mutex_lock(&philo->controller->ultimate_lock);
	if (philo->controller->win_flag > 0)
	{
		pthread_mutex_unlock(&philo->controller->ultimate_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->controller->ultimate_lock);
	return (0);
}

int	execute_routine(t_philo *philo, int i)
{
	if ((i <= philo->target_meals || philo->target_meals == -1)
		&& philo->controller->dead_flag == 0)
		if (philo_eat(philo) != 0)
			return (1);
	if ((i <= philo->target_meals || philo->target_meals == -1))
		philo_sleep_action(philo);
	if ((i <= philo->target_meals || philo->target_meals == -1))
		philo_think_action(philo);
	if (i >= philo->controller->n_times_to_eat
		& philo->controller->n_times_to_eat > 0)
	{
		pthread_mutex_lock(&philo->controller->ultimate_lock);
		philo->controller->win_flag = true;
		pthread_mutex_unlock(&philo->controller->ultimate_lock);
		return (1);
	}
	if (check_break(philo))
		return (1);
	return (0);
}
