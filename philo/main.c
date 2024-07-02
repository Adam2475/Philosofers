/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/07/02 18:10:13 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *philo_pointer)
{
	t_philo	*philo;
	int		tmp;

	tmp = 0;
	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->controller->meal_lock);
		tmp = get_time() - philo->last_meal;
		pthread_mutex_unlock(&philo->controller->meal_lock);
		// pthread_mutex_lock(&philo->controller->timeout_lock);
		// tmp = philo->last_meal;
		// printf("%d\n", tmp);
		// printf("%lu\n", get_time());
		// pthread_mutex_unlock(&philo->controller->meal_lock);
		// pthread_mutex_lock(&philo->controller->timeout_lock);
		if (check_death(philo, 0) != 0 || (size_t)tmp >= philo->time_to_die)
		{
			//printf("%lu\n", get_time() - philo->last_meal);
			//printf("%zu\n", philo->last_meal);
			pthread_mutex_lock(&philo->controller->dead_lock);
			philo->controller->exit_flag = true;
			pthread_mutex_unlock(&philo->controller->dead_lock);
			//check_death(philo, 1);
			return (NULL);
		}
			
		ft_usleep(1);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_controller	*controller;
	int				data[3];

	controller = (t_controller *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&controller->state_lock);
		pthread_mutex_lock(&controller->dead_lock);

		data[0] = controller->dead_flag;
		data[1] = controller->win_flag;
		data[2] = controller->exit_flag;

		pthread_mutex_unlock(&controller->state_lock);
		pthread_mutex_unlock(&controller->dead_lock);

		if ( data[0] > 0 || data[1] > 0 || data[2])
		{
			pthread_mutex_lock(&controller->dead_lock);
			controller->dead_flag = true;
			pthread_mutex_unlock(&controller->dead_lock);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	init_routine(t_controller *controller)
{
	int	i;

	i = 0;
	if (pthread_create(&controller->supervisor_id, NULL, &supervisor, (void *)controller) != 0)
	 	return (1);
	while (i < controller->num_of_philos)
	{
		if (pthread_create(&controller->tid[i], NULL, &routine, &controller->philos[i]) != 0)
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

	if (pthread_create(&philo->supervisor_id, NULL, &monitoring, (void *)philo) != 0)
	 	exit(1);
	while (check_death(philo, 0) != true || philo->controller->exit_flag != true || philo->controller->win_flag)
	{
		if (philo->controller->dead_flag > 0 || philo->controller->win_flag > 0 || philo->controller->exit_flag > 0)
			break;
		if ((i <= philo->target_meals || philo->target_meals == -1) && philo->controller->dead_flag == 0)
		{
				//printf("philo :%d iteration: %d dead_flag: %d\n", philo->id, i,philo->controller->dead_flag);
				if (philo_eat(philo) != 0)
					break;
		}
		if ((i <= philo->target_meals || philo->target_meals == -1))
		{
			pthread_mutex_lock(&philo->controller->dead_lock);
			if (philo->controller->dead_flag == 0)
			{
				pthread_mutex_unlock(&philo->controller->dead_lock);
				philo_sleep(philo);
			}
			else
				pthread_mutex_unlock(&philo->controller->dead_lock);
		}
		if ((i <= philo->target_meals || philo->target_meals == -1))
		{
			pthread_mutex_lock(&philo->controller->dead_lock);
			int tmp = philo->controller->dead_flag;
			pthread_mutex_unlock(&philo->controller->dead_lock);
			if (tmp == 0)
				philo_think(philo);
		}
		if (i >= philo->controller->n_times_to_eat && philo->controller->n_times_to_eat > 0)
		{
			pthread_mutex_lock(&philo->controller->ultimate_lock);
			philo->controller->win_flag = true;
			pthread_mutex_unlock(&philo->controller->ultimate_lock);
			break;
		}
		if (philo->controller->dead_flag > 0 || philo->controller->win_flag > 0 || philo->controller->exit_flag > 0)
			break;
		i++;
	}
	if (pthread_join(philo->supervisor_id, NULL) != 0)
		exit(1);
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
		return (case_one(&controller));
	init_philos(&controller);
	free_exit_multi(&controller);
	return (0);
}
