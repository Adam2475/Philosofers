/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/09 18:58:50 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	long unsigned end_time;
	long unsigned start;

	start = get_time();
	end_time = philo->controller->start_time + philo->time_to_die;
	take_forks(philo);
	philo_print(philo, 2);
	philo_print(philo, 2);
	philo_print(philo, 1);
	// if (eat_time_setter(philo, start) != 0)
	// {
	// 	philo->controller->exit_flag = true;
	// 	exit(3);
	// }
	eat_time_setter(philo, start);
	ft_usleep(philo->time_to_eat);
	philo->meal_num += 1;
	forks_down(philo);
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
	printf("%sms philo %d is thinking!\n",timestamp, philo->id);
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
}

void	philo_die(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->write_lock);
	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);
	philo->controller->dead_flag = true;
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
	exit(1);
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
