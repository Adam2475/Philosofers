/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:30:44 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/18 19:47:24 by adapassa         ###   ########.fr       */
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

int	controller_init(t_controller *elem, char **av)
{
	elem->num_of_philos = ft_atoi(av[1]);
	elem->time_to_die = (size_t)ft_atoi(av[2]);
	elem->time_to_eat = (size_t)ft_atoi(av[3]);
	elem->time_to_sleep = (size_t)ft_atoi(av[4]);
	elem->dead_flag = false;
	elem->start_time = get_time();
	if (av[5])
		elem->n_times_to_eat = ft_atoi(av[5]);
	else
		elem->n_times_to_eat = -1;
	if (elem->time_to_die < 1 || elem->time_to_sleep < 1
		|| elem->time_to_eat < 1)
		return (1);
	return (0);
}
