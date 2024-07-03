/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:58:01 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/03 13:33:39 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_exit(t_controller *controller)
{
	if (controller->philos)
		free(controller->philos);
	if (controller->tid)
		free(controller->tid);
	if (controller->philos)
		free(controller->forks);
}

static	void	*routine_solo(void *philo_pointer)
{
	t_philo		*philo;
	char		*timestamp;

	philo = (t_philo *)philo_pointer;
	while (philo->controller->dead_flag == false)
	{
		if (get_time() - philo->controller->start_time
			>= philo->controller->time_to_die)
		{
			timestamp = ft_itoa(get_time() - philo->controller->start_time);
			printf("%sms, philo %d: has died!\n", timestamp, philo->id);
			philo->controller->dead_flag = true;
			free(timestamp);
			return (NULL);
		}
	}
	return (NULL);
}

void	init_philo(t_controller *controller)
{
	controller->philos = (t_philo *)malloc(sizeof(t_philo) * 1);
	controller->tid = (pthread_t *)malloc(sizeof(pthread_t) * 1);
	controller->philos[0].time_to_die = controller->time_to_die;
	controller->philos[0].time_to_eat = controller->time_to_eat;
	controller->philos[0].time_to_sleep = controller->time_to_sleep;
	controller->philos[0].dead_flag = false;
	controller->philos[0].target_meals = controller->n_times_to_eat;
	controller->philos[0].id = 1;
	controller->philos[0].controller = controller;
	controller->philos[0].fork_l = &controller->forks[0];
	printf("%lums philo %d: has taken a fork\n", (get_time()
			- controller->start_time), controller->philos[0].id);
}

int	case_one(t_controller *controller)
{
	controller->start_time = get_time();
	init_philo(controller);
	if (pthread_create(&controller->tid[0], NULL,
			&routine_solo, &controller->philos[0]) != 0)
	{
		printf("exited from the routine process!\n");
		exit(1);
	}
	pthread_join(controller->tid[0], NULL);
	free(&controller->philos[0]);
	free(controller->tid);
	return (0);
}
