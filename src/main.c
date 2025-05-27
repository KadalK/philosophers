/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:10:55 by kapinarc          #+#    #+#             */
/*   Updated: 2025/04/25 20:10:55 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_doomsday(t_data *data)
{
	bool	value;

	pthread_mutex_lock(&data->doomsday_mutex);
	value = data->doomsday;
	pthread_mutex_unlock(&data->doomsday_mutex);
	return (value);
}

void	set_doomsday(t_data *data, bool value)
{
	pthread_mutex_lock(&data->doomsday_mutex);
	data->doomsday = value;
	pthread_mutex_unlock(&data->doomsday_mutex);
}

bool	thread_creat_n_join(t_data *data, pthread_t *thread)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&supervisor, NULL, big_brother, data) != 0)
		return (false);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_join(supervisor, NULL) != 0)
		return (false);
	return (true);
}

bool	thread_creator(t_data *data)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread)
	{
		free_init(data);
		return (false);
	}
	if (!thread_creat_n_join(data, thread))
	{
		free(thread);
		return (false);
	}
	free(thread);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (valid_args(ac, av) == -1)
		return (1);
	if (!init(&data, av))
	{
		return (1);
	}
	if (lonely_philo(data))
	{
		free_init(data);
		return (0);
	}
	thread_creator(data);
	free_init(data);
	return (0);
}
