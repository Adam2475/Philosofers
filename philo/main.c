/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/15 16:31:35 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	//t_philo **philo;
	t_controller controller;

	if (ac < 5 || ac > 6)
		return (printf("wrong arguments number\n"));

	if (arg_parser(av) != 0)
		return (printf("bad argument formatting\n"));

	// printf("all good\n");
	//printf("%d\n", controller_init(&controller, av));
	if (controller_init(&controller, av) != 0)
		return (printf("bad time input\n"));
	// init_philo(&philo, &controller);


	

	//Debug
	printf("num of philos: %d\n", controller.num_of_philos);
	printf("time to die: %zu\n", controller.time_to_die);
	printf("time to eat: %zu\n", controller.time_to_eat);
	printf("time to sleep: %zu\n", controller.time_to_sleep);
	printf("number of times each philosofer must eat: %d\n", controller.n_times_to_eat);

	return (0);
}
