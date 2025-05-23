/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:51:51 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/23 17:56:02 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_msg(int mode)
{
	if (mode == 0)
	{
		ft_putendl_fd("usage: <number_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]", 2);
	}
	else if (mode == 1)
	{
		ft_putendl_fd("ERROR:\nWrong arguments.", 2);
	}
	else if (mode == 2)
	{
		ft_putendl_fd("ERROR:\nDo not set the value too high.", 2);
	}
}

int	usage_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		error_msg(0);
		return (-1);
	}
	return (0);
}

int	wrong_arg(char *x)
{
	if (ft_strlen(x) == 0)
	{
		error_msg(1);
		return (-1);
	}
	return (0);
}

int	all_longs_valid(char **av)
{
	int	x;

	if (ft_strlen(av[1]) > 10 || (ft_strlen(av[1]) == 10
			&& ft_strncmp("2147483647", av[1], 10) < 0))
	{
		error_msg(2);
		return (-1);
	}
	x = 2;
	while (av[x])
	{
		if (ft_strlen(av[x]) > 19 || (ft_strlen(av[x]) == 19
				&& ft_strncmp("9223372036854775807", av[x], 19) < 0))
		{
			error_msg(2);
			return (-1);
		}
		x++;
	}
	return (0);
}

int	valid_args(int ac, char **av)
{
	int	x;
	int	y;

	x = 1;
	if (usage_arg(ac) == -1)
		return (-1);
	if (all_longs_valid(av) == -1)
		return (-1);
	while (av[x])
	{
		y = 0;
		if (wrong_arg(av[x]) == -1)
			return (-1);
		while (av[x][y])
		{
			if (!ft_isdigit(av[x][y]))
			{
				return (-1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
