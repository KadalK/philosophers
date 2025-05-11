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

long	ft_atol(const char *str)
{
	int					sign;
	unsigned long long	res;
	int					i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res > (unsigned long long)LLONG_MAX + (sign < 0))
			return (sign == 1 ? -1 : 0);
	}
	return ((long)(res * sign));
}

int	ft_atoi(const char *nptr)
{
	return ((int)ft_atol(nptr));
}

void	ft_putendl_fd(char *s, int fd)
{
	int i;

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
	if ((c >= 'a' && c <= 'z' )||( c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}