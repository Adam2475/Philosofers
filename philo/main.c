/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/06/25 12:14:22 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// *supervisor(void *philo_pointer)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)philo_pointer;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->controller->meal_lock);
// 		if (check_death(philo, 0) != 0 || get_time() - philo->last_meal >= philo->time_to_die)
// 		{
// 			philo_die(philo);

// 			pthread_mutex_lock(&philo->controller->dead_lock);
// 			philo->controller->exit_flag = true;
// 			philo->controller->win_flag = true;
// 			philo->controller->dead_flag = true;
// 			pthread_mutex_unlock(&philo->controller->dead_lock);
// 			pthread_mutex_unlock(&philo->controller->meal_lock);
// 			break;
// 		}
// 		pthread_mutex_unlock(&philo->controller->meal_lock);

// 		pthread_mutex_lock(&philo->controller->dead_lock);
// 		if (philo->controller->dead_flag == true)
// 		{
// 			pthread_mutex_unlock(&philo->controller->dead_lock);
// 			break;
// 		}
// 		pthread_mutex_unlock(&philo->controller->dead_lock);

// 		ft_usleep(1);
// 	}
// 	return (NULL);
// } 

void	*monitoring(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->controller->lock);
		if (philo->controller->living_flag != 0)
		{
			//pthread_mutex_lock(&philo->controller->ultimate_lock);
			pthread_mutex_unlock(&philo->controller->lock);
			//pthread_mutex_unlock(&philo->controller->ultimate_lock);
			break;
		}
		pthread_mutex_unlock(&philo->controller->lock);

		pthread_mutex_lock(&philo->controller->meal_lock);
		if (check_death(philo, 0) != 0 || get_time() - philo->last_meal >= philo->time_to_die)
		{
			pthread_mutex_unlock(&philo->controller->meal_lock);

			
			pthread_mutex_lock(&philo->controller->dead_lock);
			pthread_mutex_lock(&philo->controller->ultimate_lock);
			philo->controller->exit_flag = true;
			pthread_mutex_unlock(&philo->controller->ultimate_lock);
			pthread_mutex_unlock(&philo->controller->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->controller->meal_lock);
		ft_usleep(1);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_controller *controller;

	controller = (t_controller *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&controller->ultimate_lock);
		if (controller->dead_flag > 0 || controller->exit_flag > 0)
		{
			pthread_mutex_unlock(&controller->ultimate_lock);
			//printf("case death exit");
			//controller->stop_he_already_dead = true;
			pthread_mutex_lock(&controller->dead_lock);
			pthread_mutex_lock(&controller->lock);
			controller->dead_flag = true;
			controller->living_flag = true;
			pthread_mutex_unlock(&controller->dead_lock);
			pthread_mutex_unlock(&controller->lock);
			
			return (NULL);
		}
		//printf("%d\n", controller->dead_flag);
		pthread_mutex_unlock(&controller->ultimate_lock);
		ft_usleep(2);
	}
	return (NULL);
}

int	init_routine(t_controller *controller)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	if (pthread_create(&controller->supervisor_id, NULL, &supervisor, (void *)controller) != 0)
	 	return (1);

	while (i < controller->num_of_philos)
	{
		if (pthread_create(&controller->tid[i], NULL, &routine, &controller->philos[i]) != 0)
		{
			printf("error in initializing routine!\n");
			return (1);
		}
		ft_usleep(1);
		i++;
	}
	j = i;
	while (j > 0)
	{
		j--;
		pthread_join(controller->tid[j], NULL);
	}
	if (pthread_join(controller->supervisor_id, NULL) != 0)
	 	return (1);
	//free_exit_multi(controller);
	return (0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = (t_philo *)philo_pointer;
	philo->last_meal = philo->controller->start_time;
	//pthread_mutex_init(&philo->controller->state_lock, NULL);

	if (pthread_create(&philo->supervisor_id, NULL, &monitoring, (void *)philo) != 0)
	 	exit(1);

	while (check_death(philo, 0) != true || philo->controller->exit_flag != true)
	{
		if (check_death(philo, 0) != 0 || get_time() - philo->last_meal >= philo->time_to_die)
		{
			//philo_die(philo);
			philo->controller->exit_flag = true;
			philo->controller->win_flag = true;
			philo->controller->dead_flag = true;
			//printf("ciao");
			break;
		}

		if (philo->controller->dead_flag > 0)
			break;

		if ((i <= philo->target_meals || philo->target_meals == -1) && philo->controller->dead_flag == 0)
		{
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

		pthread_mutex_lock(&philo->controller->dead_lock);
		if ((i <= philo->target_meals || philo->target_meals == -1))
		{
			pthread_mutex_unlock(&philo->controller->dead_lock);
			pthread_mutex_lock(&philo->controller->lock);
			int tmp = philo->controller->dead_flag;
			pthread_mutex_unlock(&philo->controller->lock);


			if (tmp == 0)
				philo_think(philo);
			// else
			// {
			// 	//pthread_mutex_lock(&philo->controller->ultimate_lock);
			// 	pthread_mutex_unlock(&philo->controller->dead_lock);
			// 	// pthread_mutex_unlock(&philo->controller->lock);
			// 	// //pthread_mutex_unlock(&philo->controller->ultimate_lock);
			// }
		}

		if (i >= philo->controller->n_times_to_eat && philo->controller->n_times_to_eat > 0)
		{
			pthread_mutex_lock(&philo->controller->ultimate_lock);
			philo->controller->win_flag = true;
			philo->controller->exit_flag = true;
			pthread_mutex_unlock(&philo->controller->ultimate_lock);
			break;
		}

		pthread_mutex_lock(&philo->controller->meal_lock);
		if (philo->controller->dead_flag == true)
		{
			if (!philo->controller->stop_he_already_dead)
				philo_die(philo);
			philo->controller->win_flag = true;
			philo->controller->exit_flag = true;
			pthread_mutex_unlock(&philo->controller->meal_lock);
			break;
		}
		else
			pthread_mutex_unlock(&philo->controller->meal_lock);
		i++;
	}
	pthread_detach(philo->supervisor_id);
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
	ft_usleep(100);
	free_exit_multi(&controller);
	return (0);
}
