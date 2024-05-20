/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/20 19:58:06 by adapassa         ###   ########.fr       */
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
		{
			controller->philos[i].fork_r = &controller->forks[i - 1];
		}
		controller->philos[i].fork_l = &controller->forks[i];
		//Debugging
		// printf("adress of fork number: %d : %p\n", i,  &controller->forks[i]);
		// printf("philo num : %d fork_l : %p\n", i,  controller->philos[i].fork_l);
		// printf("philo num : %d fork_r : %p\n", i, controller->philos[i].fork_r);
		// controller->philos[i].fork_l = &controller->forks[i];
		// printf("philo num : %d fork_l : %p\n", i,  controller->philos[i].fork_l);
		i++;
	}
	printf("-------------------------------\nInitializing the main routine!\n-------------------------------\n");
	init_routine(controller);
}

int	init_routine(t_controller *controller)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < controller->num_of_philos)
	{
		if (pthread_create(&controller->tid[i], NULL, &routine, &controller->philos[i]) != 0)
		{
			printf("error in initializing routine!\n");
			return (1);
		}
		i++;
	}
	j = i;
	while (j > 0)
	{
		j--;
		ft_usleep(1);
		pthread_join(controller->tid[j], NULL);
	}
	return (0);
}

void	init_multiple(t_controller *controller)
{
	return ;
}

static	void	ft_init_mutex(t_controller *controller)
{
	int	i;

	i = 0;
	while (i < controller->num_of_philos)
	{
		if (pthread_mutex_init(&controller->forks[i], NULL) != 0)
		{
			printf("error initializing forks!\n");
			exit(1);
		}
		i++;
	}
}

static	void	init_forks(t_controller *controller)
{
	controller->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * controller->num_of_philos);
	ft_init_mutex(controller);
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
		controller->philos[i].meals_num = 0;
		controller->philos[i].id = i + 1;
		controller->philos[i].controller = controller;
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

static	void	*routine_solo(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->controller->dead_flag == false)
	{
		if (get_time() - philo->controller->start_time >= philo->controller->time_to_die)
		{
			philo_die(philo);
			exit(1);
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	// t_philo	*philo;
	// int		i;

	// philo = (t_philo *)philo_pointer;
	// i = 0;
	// while (i < philo[0].target_meals)
	// {
	// 	i++;
	// 	philo[0].meals_num += 1;
	// 	printf("meal n: %d\n", philo[0].meals_num);
	// }
	printf("hello world");
	return (NULL);
}

static	void	free_exit(t_controller *controller)
{
	free(controller->philos);
	free(controller->tid);
	// free(controller->forks);
	exit(0);
}

static	void	case_one(t_controller *controller)
{
	controller->start_time = get_time();
	controller->philos = (t_philo *)malloc(sizeof(t_philo) * 1);
	controller->tid = (pthread_t *)malloc(sizeof(pthread_t) * 1);
	init_philos(controller);

	if (pthread_create(&controller->tid[0], NULL, &routine_solo, &controller->philos[0]) != 0)
	{
		printf("exited from the routine process!\n");
		exit(1);
	}

	pthread_join(controller->tid[0], NULL);

	free_exit(controller);
	return ;
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
		case_one(&controller);
	// else
	// 	init_multiple(&controller);

	init_philos(&controller);

	return (0);
}
