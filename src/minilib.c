/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:04 by kapinarc          #+#    #+#             */
/*   Updated: 2025/04/28 15:04:04 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_bis_atol(const char *str, size_t *i, int *conv)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || (str[*i] == ' '))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*conv *= -1;
		(*i)++;
	}
}

long	ft_atol(const char *str)
{
	int					conv;
	size_t				i;
	unsigned long long	res;

	conv = 1;
	i = 0;
	res = 0;
	ft_bis_atol(str, &i, &conv);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > LLONG_MAX && conv < 0)
			return (0);
		if (res > LLONG_MAX)
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > LLONG_MAX && conv < 0)
		return (0);
	if (res > LLONG_MAX)
		return (-1);
	return (((long)res) * conv);
}

int	ft_atoi(const char *nptr)
{
	return ((int)ft_atol(nptr));
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 2);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
