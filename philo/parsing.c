/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:29:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/25 11:19:37 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->controller->ultimate_lock);
	if (nb)
		philo->controller->exit_flag = true;
	if (philo->controller->exit_flag)
	{
		pthread_mutex_unlock(&philo->controller->ultimate_lock);
		philo_die(philo);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->controller->ultimate_lock);
	return (0);
}

int arg_parser(char **av)
{
	int	i;

	i = 1;
	if (ft_strncmp(av[1], "0", 1) == 0 || ft_strncmp(av[2], "0", 1) == 0
		|| ft_strncmp(av[3], "0", 1) == 0
		|| ft_strncmp(av[4], "0", 1) == 0)
		return (1);
	while (av[i])
	{
		if (str_is_digit(av[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
