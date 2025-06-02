/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:35:17 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/27 21:00:09 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	args_init(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->doomsday = false;
}

static	bool	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_timestamp_in_ms();
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (free_init(data), false);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (free_init(data), false);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = get_timestamp_in_ms();
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].l_fork->available = true;
		data->philos[i].r_fork->available = true;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
	return (true);
}

static	void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->doomsday_mutex, NULL);
	pthread_mutex_init(&data->sleep_mutex, NULL);
}

bool	init(t_data **data, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		free_init(*data);
		return (false);
	}
	memset(*data, 0, sizeof(t_data));
	args_init(*data, av);
	if (!data_init(*data))
		return (false);
	mutex_init(*data);
	return (true);
}

void	free_init(t_data *data)
{
	if (data && data->forks)
		free(data->forks);
	if (data && data->philos)
		free(data->philos);
	if (data)
		free(data);
}
