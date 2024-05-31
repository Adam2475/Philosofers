/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/31 19:10:27 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	distribute_forks(t_controller *controller)
{
	int	i;

	i = 0;
	while (i < controller->num_of_philos)
	{
		if (i == 0)
			controller->philos[i].fork_r = &controller->forks[controller->num_of_philos - 1];
		else
			controller->philos[i].fork_r = &controller->forks[i - 1];

		controller->philos[i].fork_l = &controller->forks[i];
		i++;
	}
	init_routine(controller);
}

void	init_philos(t_controller *controller)
{
	int	i;
	controller->philos = (t_philo *)malloc(sizeof(t_philo) * controller->num_of_philos);
	controller->tid = (pthread_t *)malloc(sizeof(pthread_t) * controller->num_of_philos);

	i = 0;
	init_forks(controller);
	while (i < controller->num_of_philos)
	{
		controller->philos[i].time_to_die = controller->time_to_die;
		controller->philos[i].time_to_eat = controller->time_to_eat;
		controller->philos[i].time_to_sleep = controller->time_to_sleep;
		controller->philos[i].dead_flag = false;
		controller->philos[i].target_meals = controller->n_times_to_eat;
		controller->philos[i].id = i + 1;
		controller->philos[i].controller = controller;

		controller->philos[i].last_meal = get_time() - controller->start_time;
		controller->philos[i].meal_num = 0;
		i++;
	}
	if (controller->num_of_philos != 1)
		distribute_forks(controller);
	else
	{
		controller->philos[0].fork_l = &controller->forks[0];
		printf("%lums philo %d: has taken a fork\n", (get_time() - controller->start_time), controller->philos[0].id);
	}
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->controller->dead_flag == false)
	{
		if (philo->eating_flag != true)
		{
			if (get_time() - philo->controller->start_time - philo->last_meal >= philo->time_to_die)
			{
				philo_die(philo);
				philo->controller->dead_flag = true;
			}
		}
		if (philo->controller->n_times_to_eat != -1)
		{
			if (philo->meal_num > philo->controller->n_times_to_eat)
			{
				printf("win");
				philo->controller->win_flag = true;
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (pthread_create(&philo->supervisor_id, NULL, &supervisor, (void *)philo) != 0)
	 	return (NULL);
	while (philo->controller->dead_flag != true || philo->controller->win_flag != true)
	{
		if (philo->controller->dead_flag == true)
		{
			philo_die(philo);
			exit(1);
		}
		if (philo->controller->win_flag == true)
		{
			printf("win");
			return (NULL);
		}
		if (philo->id % 2 == 1)
		{
			philo_eat(philo);
			philo_sleep(philo);
		}
		if (philo->id % 2 == 0)
		{
			philo_sleep(philo);
			philo_eat(philo);
		}
	}
	if (pthread_join(philo->supervisor_id, NULL))
		return (NULL);
	return (NULL);
}

int main(int ac, char **av)
{
	t_controller	controller;

	if (ac < 5 || ac > 6)
		return (printf("wrong arguments number\n"));
	if (arg_parser(av) != 0)
		return (printf("bad argument formatting\n"));
	if (controller_init(&controller, av) != 0)
		return (printf("bad time input\n"));
	if (controller.num_of_philos == 1)
	{
		case_one(&controller);
		return (0);
	}

	init_philos(&controller);
	
	free(controller.philos);
	free(controller.tid);
	free(controller.forks);

	return (0);
}
