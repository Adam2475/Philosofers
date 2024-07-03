/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/03 13:21:29 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	int	tmp;

	take_forks(philo);
	pthread_mutex_lock(&philo->controller->dead_lock);
	tmp = philo->controller->dead_flag;
	if (tmp)
	{
		forks_down(philo);
		pthread_mutex_unlock(&philo->controller->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->controller->dead_lock);
	philo_print(philo, 2);
	philo_print(philo, 2);
	philo_print(philo, 1);
	ft_usleep(philo->time_to_eat);
	eat_time_setter(philo);
	philo->meal_num += 1;
	forks_down(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, 3);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->write_lock);
	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms philo %d is thinking!\n", timestamp, philo->id);
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
}

void	philo_die(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->write_lock);
	if (philo->controller->time_to_die < philo->controller->time_to_eat)
		timestamp = ft_itoa(philo->controller->time_to_die);
	else if (!philo->last_meal || (philo->time_to_eat * 2) > philo->time_to_die)
		timestamp = ft_itoa(philo->time_to_die);
	else
		timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
	pthread_mutex_lock(&philo->controller->ultimate_lock);
	philo->controller->stop_he_already_dead = true;
	pthread_mutex_unlock(&philo->controller->ultimate_lock);
}

void	philo_print(t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	if (unlock == 1)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: is eating!\n", timestamp, philo->id);
		free(timestamp);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
	else if (unlock == 2)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: has taken a fork!\n", timestamp, philo->id);
		free(timestamp);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
	else if (unlock == 3)
	{
		pthread_mutex_lock(&philo->controller->write_lock);
		printf("%sms, philo %d: is sleeping!\n", timestamp, philo->id);
		free(timestamp);
		pthread_mutex_unlock(&philo->controller->write_lock);
	}
}
