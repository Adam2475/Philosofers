/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/31 19:40:04 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	philo->eating_flag = true;
	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	philo_print(philo, 2);
	philo_print(philo, 2);
	philo_print(philo, 1);
	ft_usleep(philo->time_to_eat);
	philo->last_meal = get_time() - philo->controller->start_time;
	philo->meal_num += 1;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, 3);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms philo %d is thinking!\n",timestamp, philo->id);
	free(timestamp);
}

void	philo_die(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->dead_lock);
	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);
	philo->controller->dead_flag = true;
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->dead_lock);
}

void	philo_print(t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	if (unlock == 1)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: is eating!\n", timestamp, philo->id);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
	if (unlock == 2)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: has taken a fork!\n", timestamp, philo->id);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
	if (unlock == 3)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: is sleeping!\n", timestamp, philo->id);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
}
