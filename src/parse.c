/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:51:51 by kapinarc          #+#    #+#             */
/*   Updated: 2025/04/29 15:51:51 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_msg(int mode)
{
	if (mode == 1)
	{
		ft_putendl_fd("usage: <number_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]", 2);
	}
	else if (mode == 2)
	{
		ft_putendl_fd("ERROR:\nDo not set the value too high or "
			"negativ one.", 2);
	}
}

int	valid_args(int ac, char **av)
{
	int	x;
	int	y;

	x = 1;
	if (ac < 5 || ac > 6)
	{
		error_msg(1);
		return (-1);
	}
	while (av[x])
	{
		y = 0;
		while (av[x][y])
		{
			if (ft_isalpha(av[x][y]) || ft_atol(av[x]) <= 0)
			{
				error_msg(2);
				return (-1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
