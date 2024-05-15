/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:57:29 by adapassa          #+#    #+#             */
/*   Updated: 2024/05/15 17:37:56 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (printf("error while getting the time!\n"));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

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
	if (res > INT_MAX)
		return (0);
	return (sign * res);
}
