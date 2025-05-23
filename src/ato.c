/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:13:21 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/23 18:13:21 by kapinarc         ###   ########.fr       */
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
