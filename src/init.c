/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:35:17 by kapinarc          #+#    #+#             */
/*   Updated: 2025/04/29 17:35:17 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	args_init(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else if (!av[5])
		data->must_eat = -1;
	data->doomsday = false;
}

static	bool	data_init(t_data *data)
{
	int i;

	i =  0;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (false);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

bool	init(t_data **data, char **av)
{
	*data = malloc(sizeof (t_data));
	if (!*data)
		return (false);
	memset(*data, 0, sizeof(t_data));
	args_init(*data, av);
	if (!data_init(*data))
		return (false);
	return (true);
}