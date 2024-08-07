/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/03 15:05:54 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *philo_pointer)
{
	t_philo		*philo;
	int			tmp;

	tmp = 0;
	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->controller->meal_lock);
		tmp = get_time() - philo->last_meal;
		pthread_mutex_unlock(&philo->controller->meal_lock);
		if (check_death(philo, 0) != 0 || (size_t)tmp >= philo->time_to_die)
		{
			pthread_mutex_lock(&philo->controller->state_lock);
			philo->controller->exit_flag = true;
			pthread_mutex_unlock(&philo->controller->state_lock);
			return (NULL);
		}
		ft_usleep(3);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_controller	*controller;
	int				data[2];

	controller = (t_controller *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&controller->state_lock);
		data[1] = controller->exit_flag;
		pthread_mutex_unlock(&controller->state_lock);
		pthread_mutex_lock(&controller->ultimate_lock);
		data[0] = controller->win_flag;
		pthread_mutex_unlock(&controller->ultimate_lock);
		if (data[0] > 0 || data[1] > 0)
		{
			pthread_mutex_lock(&controller->dead_lock);
			controller->living_flag = true;
			pthread_mutex_unlock(&controller->dead_lock);
			return (NULL);
		}
		ft_usleep(10);
	}
	return (NULL);
}

int	init_routine(t_controller *controller)
{
	int	i;

	i = 0;
	if (pthread_create(&controller->supervisor_id, NULL,
			&supervisor, (void *)controller) != 0)
		return (1);
	while (i < controller->num_of_philos)
	{
		if (pthread_create(&controller->tid[i], NULL,
				&routine, &controller->philos[i]) != 0)
			return (printf("error in initializing routine!\n"));
		ft_usleep(1);
		i++;
	}
	while (i-- > 0)
		pthread_join(controller->tid[i], NULL);
	return (pthread_join(controller->supervisor_id, NULL) != 0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = (t_philo *)philo_pointer;
	philo->last_meal = philo->controller->start_time;
	if (pthread_create(&philo->supervisor_id, NULL,
			&monitoring, (void *)philo) != 0)
		exit(1);
	while (check_death(philo, 0) != true)
	{
		if (execute_routine(philo, i) > 0)
			break ;
		i++;
	}
	if (pthread_join(philo->supervisor_id, NULL) != 0)
		exit(1);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_controller	controller;

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
