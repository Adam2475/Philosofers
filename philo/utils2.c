/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:58:40 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/09 18:47:33 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(__useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	if (!(str_num = (char *)malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}

void	die_eating(t_philo *philo)
{
	char	*timestamp;

	pthread_mutex_lock(&philo->controller->write_lock);

	timestamp = ft_itoa( get_time() - philo->controller->start_time + (philo->time_to_die - philo->time_to_eat));
	printf("%sms, philo %d: couldn't finish eating!\n", timestamp, philo->id);
	free(timestamp);
	exit(1);
	pthread_mutex_unlock(&philo->controller->write_lock);
}

int	eat_time_setter(t_philo *philo, long unsigned start)
{
	pthread_mutex_lock(&philo->controller->meal_lock);
	(void)start;
	// if (get_time() - philo->last_meal + philo->time_to_eat >= philo->time_to_die)
	// {
	// 	die_eating(philo);
	// 	pthread_mutex_unlock(&philo->controller->meal_lock);
	// 	return (1);
	// }
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->controller->meal_lock);
	return (0);
}