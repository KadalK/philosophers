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

int	valid_args(int ac, char **av)
{
	int	x;
	int	y;

	x = 1;
	if (ac != 5)
	{
		printf("ERROR :\nPut <number_of_philosophers>, <time_to_die>, "
			   "<time_to_eat>, <time_to_sleep>\n");
		return (-1);
	}
	while (av[x])
	{
		y = 0;
		while (av[x][y])
		{
			if (ft_atol(&av[x][y]) < 0)
			{
				printf("ERROR :\nOnly positive numbers allowed.\n");
				return (-1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
