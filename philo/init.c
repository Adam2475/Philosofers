/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:30:44 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/15 16:21:49 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	controller_init(t_controller *elem, char **av)
{
	elem->num_of_philos = ft_atoi(av[1]);
	elem->time_to_die = (size_t)ft_atoi(av[2]);
	elem->time_to_eat = (size_t)ft_atoi(av[3]);
	elem->time_to_sleep = (size_t)ft_atoi(av[4]);
	elem->dead_flag = false;
	if (av[5])
		elem->n_times_to_eat = ft_atoi(av[5]);
	else
		elem->n_times_to_eat = -1;
	if (elem->time_to_die < 1 || elem->time_to_sleep < 1
		|| elem->time_to_eat < 1)
		return (1);
	return (0);
}

// void	init_philo(t_controller *controller)
// {
	
// }
