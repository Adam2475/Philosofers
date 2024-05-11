#include "philo.h"

static int	ft_isdigit(int c)
{
	if ((c <= 57 && c >= 48))
		return (1);
	return (0);
}

int str_is_digit(const char *str)
{
    while (*str)
	{
        if (ft_isdigit(*str) != 1)
		{
            return (1); // Not a digit
        }
        str++;
    }
    return (0); // All characters are digits
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (sign * res);
}
