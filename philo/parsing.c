#include "philo.h"

int arg_parser(char **av)
{
	int	i;

	i = 1;
	if (av[1] == 0 || av[2] == 0 || av[3] == 0
		|| av[4] == 0)
		return (1);

	while (av[i])
	{
		if (str_is_digit(av[i]) != 0)
		{
			printf("%d\n", str_is_digit(av[i]));
			return (1);
		}
		i++;
	}
	return (0);
}
