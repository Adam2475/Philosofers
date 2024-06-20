/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/20 16:37:45 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int 	final_flag;

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

void	*supervisor(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	while (1 && philo->controller->exit_flag != true)
	{
		pthread_mutex_lock(&philo->controller->meal_lock);
		if (check_death(philo, 0) != 0 || get_time() - philo->last_meal >= philo->time_to_die)
		{
			pthread_mutex_unlock(&philo->controller->meal_lock);
			philo_die(philo);
			philo->controller->exit_flag = true;
			final_flag = 1;
			break;
		}
		pthread_mutex_unlock(&philo->controller->meal_lock);
		ft_usleep(1);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = (t_philo *)philo_pointer;
	philo->last_meal = philo->controller->start_time;
	if (pthread_create(&philo->supervisor_id, NULL, &supervisor, (void *)philo) != 0)
	 	return (NULL);
	while (check_death(philo, 0) != true || philo->controller->exit_flag != true)
	{
		printf("%d\n", final_flag);
		if (final_flag > 0)
		{
			printf("trigger routine exit control!!\n");
			break;
		}
		if (philo->controller->dead_flag == true)
		{
			printf("trigger routine exit control!!\n");
			exit(1);
		}
		if (check_death(philo, 0) != 0)
		{
			printf("exiting from routine for death");
			exit(1);
		}
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (i >= philo->controller->n_times_to_eat && philo->controller->n_times_to_eat > 0)
		{
			printf("exiting from routine for winning");
			exit(1);
		}
		printf("%d\n", final_flag);
		if (final_flag > 0)
		{
			printf("trigger routine exit control!!\n");
			break;
		}
		i++;
	}
	if (pthread_join(philo->supervisor_id, NULL))
		return (NULL);
	return (NULL);
}

int main(int ac, char **av)
{
	t_controller	controller;

	final_flag = 0;
	if (ac < 5 || ac > 6)
		return (printf("wrong arguments number\n"));
	if (arg_parser(av) != 0)
		return (printf("bad argument formatting\n"));
	if (controller_init(&controller, av) != 0)
		return (printf("bad time input\n"));
	if (controller.num_of_philos == 1)
		return (case_one(&controller));
	init_philos(&controller);
	free_exit_multi(&controller);
	return (0);
}
