/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:33:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/18 20:04:40 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void    take_forks()
// {
// 	char    *timestamp;

// 	timestamp = ft_itoa(get_time() - philo->env->start_time);
// 	printf("philo has taken a fork");
// }

void    philo_eat()
{
	printf("philo is eating");
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

	timestamp = ft_itoa(get_time() - philo->controller->start_time);
	printf("%sms, philo %d: has died!\n", timestamp, philo->id);
}

// void    philo_print(char *msg, t_philo *philo, int unlock)
// {
// 	char    *timestamp;

// 	time
// 	timestamp = ft_itoa(get_time() - controller->start_time);
// }
