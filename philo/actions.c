/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/28 18:30:30 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void    take_forks()
// {
// 	char    *timestamp;

// 	timestamp = ft_itoa(get_time() - philo->env->start_time);
// 	printf("philo has taken a fork");
// }

void    philo_eat(t_philo *philo)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	philo_print(philo, 1);
	ft_usleep(philo->time_to_eat);
	philo->last_meal = get_time() - philo->controller->start_time;
	printf("philo: %d meal-time: %lums\n", philo->id, philo->last_meal);
	philo->meal_num += 1;
	printf("philo %d meal number: %d\n",philo->id, philo->meal_num);
}

void    philo_sleep()
{
	printf("philo is sleeping");
}

void    philo_think()
{
	printf("philo is thinking");
}

void	philo_die(t_philo *philo)
{
	char	*timestamp;

	//philo->controller->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	//pthread_mutex_lock(philo->controller->dead_lock);
	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);
	philo->controller->dead_flag = true;
	free(timestamp);
	//pthread_mutex_unlock(philo->controller->dead_lock);
}

void    philo_print(t_philo *philo, int unlock)
{
	char    *timestamp;

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	if (unlock == 1)
	{
		pthread_mutex_lock(philo->controller->write_lock);
		printf("%sms, philo %d: is eating!\n", timestamp, philo->id);
		pthread_mutex_unlock(philo->controller->write_lock);
	}
		
}
