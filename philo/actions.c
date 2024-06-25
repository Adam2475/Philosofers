/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/25 09:07:36 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
 	//pthread_mutex_lock(&philo->controller->lock);
	//pthread_mutex_lock(&philo->controller->lock);
	take_forks(philo);
	
	pthread_mutex_lock(&philo->controller->dead_lock);
	if (philo->controller->dead_flag != false)
	{
		pthread_mutex_unlock(&philo->controller->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->controller->dead_lock);
	//printf("death from eat philo: %d : %d\n", philo->id, philo->controller->dead_flag);
	//pthread_mutex_unlock(&philo->controller->lock);
	philo_print(philo, 2);
	philo_print(philo, 2);
	philo_print(philo, 1);
	//pthread_mutex_lock(&philo->controller->dead_lock);
	// if (philo->controller->time_to_die < philo->controller->time_to_eat)
	// {
	// 	philo_die(philo);
	// 	forks_down(philo);
	// 	philo->controller->dead_flag = true;
	// 	return (1);
	// }
	ft_usleep(philo->time_to_eat);
	eat_time_setter(philo);
	//pthread_mutex_unlock(&philo->controller->dead_lock);
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
	printf("%sms philo %d is thinking!\n",timestamp, philo->id);
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
}

void	philo_die(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->write_lock);

	// printf("%lu\n", philo->last_meal);
	// printf("%lu\n", philo->controller->start_time);
	// printf("%lu\n", philo->last_meal - philo->controller->start_time);

	if (philo->controller->time_to_die < philo->controller->time_to_eat)
		timestamp = ft_itoa(philo->controller->time_to_die);
	else if (!philo->last_meal || (philo->time_to_eat * 2) > philo->time_to_die)
		timestamp = ft_itoa(philo->time_to_die);
	else
		timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);

	pthread_mutex_lock(&philo->controller->dead_lock);
	philo->controller->stop_he_already_dead = true;
	pthread_mutex_unlock(&philo->controller->dead_lock);
	
	free(timestamp);
	pthread_mutex_unlock(&philo->controller->write_lock);
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
