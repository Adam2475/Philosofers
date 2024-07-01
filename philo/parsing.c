/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:29:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/01 19:33:01 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, int nb)
{
	int tmp1[3];
	
	pthread_mutex_lock(&philo->controller->dead_lock);
	pthread_mutex_lock(&philo->controller->ultimate_lock);
	if (nb)
		philo->controller->dead_flag = true;
	tmp1[0] = philo->controller->stop_he_already_dead;
	tmp1[1] = philo->controller->dead_flag;
	tmp1[2] = philo->controller->win_flag;
	pthread_mutex_unlock(&philo->controller->ultimate_lock);
	pthread_mutex_unlock(&philo->controller->dead_lock);
	if (tmp1[1] && !tmp1[2])
	{
		if (tmp1[0] != true)
		{
			philo_die(philo);
			//printf("%d\n", philo->controller->stop_he_already_dead);
			return (1);
		}
	}
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
