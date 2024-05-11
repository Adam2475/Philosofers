#include "philo.h"

int	controller_init(t_controller elem, char **av)
{
	elem->time_to_die = ft_atoi(av[2]);
	elem->time_to_eat = ft_atoi(av[3]);
	elem->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		elem->n_times_to_eat = ft_atoi(av[5]);
	else
		elem->n_times_to_eat = -1;
}
