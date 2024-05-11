#include "philo.h"

int main(int ac, char **av)
{
	t_philo *philo;

	if (ac < 5 || ac > 6)
		return (printf("wrong arguments number\n"));

	if (arg_parser(av) != 0)
		return (printf("bad argument formatting\n"));

	printf("all good\n");

	return (0);
}
