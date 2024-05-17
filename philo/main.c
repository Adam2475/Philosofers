/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:47:28 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/15 17:42:16 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_multiple(t_controller *controller)
{
	controller->philos = (t_philo *)malloc(sizeof(t_philo) * controller->num_of_philos);
	controller->tid = (pthread_t *)malloc(sizeof(pthread_t) * controller->num_of_philos);
}

// static	void	distribute_forks(t_controller *cotroller)
// {

// }

static	void	ft_init_mutex(t_controller *controller)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_mutex_init(controller->forks[i]) != 0)
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

	i = 0;
	init_forks(controller);
	while (i < controller->num_of_philos)
	{
		controller->philos[i].time_to_die = controller->time_to_die;
		controller->philos[i].time_to_eat = controller->time_to_eat;
		controller->philos[i].time_to_sleep = controller->time_to_sleep;
		controller->philos[i].dead_flag = false;
		controller->philos[i].target_meals = controller->n_times_to_eat;
		//Debug
		// printf("-------------------------------------------------\n");
		// printf("number of times each philosofer must eat: %d\n", controller->philos[i].target_meals);
		// printf("time to die: %zu\n", controller->philos[i].time_to_die);
		// printf("time to eat: %zu\n", controller->philos[i].time_to_eat);
		// printf("time to sleep: %zu\n", controller->philos[i].time_to_sleep);
		i++;
	}
	if (controller->num_of_philos != 1)
		distribute_forks(controller);
	else
	{
		controller->philos[0].fork_l = controller->forks[0];
		printf("fork given to philo 1");
	}
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_pointer;
	i = 0;
	// philo[0] = (t_philo)malloc(sizeof(t_philo) * 1);
	// philo->id = 1;
	// printf("%d\n", philo->id);
	while (i < philo[0]->target_meals)
	{

	}
	// printf("time to die: %zu\n", philo[0].time_to_die);
	// printf("time to eat: %zu\n", philo[0].time_to_eat);
	// printf("time to sleep: %zu\n", philo[0].time_to_sleep);
	// printf("number of times each philosofer must eat: %d\n", philo[0].target_meals);
	// exit(1);
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

	if (pthread_create(&controller->tid[0], NULL, &routine, &controller->philos[0]) != 0)
	{
		printf("exited from the routine process!\n");
		exit(1);
	}

	// 	The pthread_join() function waits for the thread specified by thread to
    //  terminate.  If that thread has already terminated, then  pthread_join()
    //  returns immediately.  The thread specified by thread must be joinable.
	pthread_join(controller->tid[0], NULL);

	// printf("%s\n", controller->philos[0].prova);

	// while (controller->dead_flag == false)
	// 	ft_usleep(0);

	// ft_usleep(2000);

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
	else
		init_multiple(&controller);

	init_philos(&controller);

	// if (init_routine(controller) != 0)
	// 	return (printf("exited from routine\n"));

	//Debug
	printf("num of philos: %d\n", controller.num_of_philos);
	printf("time to die: %zu\n", controller.time_to_die);
	printf("time to eat: %zu\n", controller.time_to_eat);
	printf("time to sleep: %zu\n", controller.time_to_sleep);
	printf("number of times each philosofer must eat: %d\n", controller.n_times_to_eat);

	return (0);
}
