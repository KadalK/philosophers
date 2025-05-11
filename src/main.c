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

#include "../include/philo.h"

int check_death(t_data *data)
{
	int		i;
	long	current_time;
	const long time_to_die = data->time_to_die;

	i = 0;
	current_time = get_timestamp_in_ms();
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if ((current_time - data->philos[i].last_meal) >= time_to_die)
		{
//			printf("%ld ta grand mere\n", data->philos[i].last_meal);
			print_mutex(&data->philos[i], "died");
			pthread_mutex_unlock(&data->philos[i].meal_mutex);

			pthread_mutex_lock(&data->doomsday_mutex);
			data->doomsday = true;
			pthread_mutex_unlock(&data->doomsday_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (0);
}

void	*big_brother(void *arg)
{
	t_data *data;
	data = (void *)arg;
	while(!get_doomsday(data))
	{
		if (check_death(data) == 1)
		{
			pthread_mutex_lock(&data->doomsday_mutex);
			data->doomsday = true;
			pthread_mutex_unlock(&data->doomsday_mutex);
		}
		usleep(50);
	}
	return (NULL);
}

bool	get_doomsday(t_data *data)
{
	bool	value;
	pthread_mutex_lock(&data->doomsday_mutex);
	value = data->doomsday;
	pthread_mutex_unlock(&data->doomsday_mutex);
	return (value);
}

bool	thread_creat_n_join(t_data *data, pthread_t *thread)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->nb_philo)
	{
//		printf("DEBUG %d\n", i);
		if (pthread_create(&thread[i], NULL, routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
		if (pthread_create(&supervisor, NULL, big_brother, data) != 0)
			return (false);
	i = 0;
	while ( i < data->nb_philo)
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
	pthread_t *thread;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread)
		return (false);
	if (!thread_creat_n_join(data, thread))
	{
		free(thread);
		return (false);
	}
	free(thread);
	return (true);
}

int main(int ac, char **av)
{
	t_data *data;

	if (valid_args(ac, av) == - 1)
		return (1);
	if (!init(&data, av))
		return(1);
//	printf("DEBUG nb_philo = %d\n", data->nb_philo);
	thread_creator(data);
	free_init(data);
	return (0);
}