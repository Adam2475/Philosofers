#include "philo.h"
#include <limits.h>

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
			return (1);
		}
		str++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (i < n - 1))
	{
		if (s1[i] != s2[i] || i >= n)
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// lucky we don't need negative values here :)
int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	// printf("%ld\n", res);
	if (res > INT_MAX)
		return (0);
	return (sign * res);
}
