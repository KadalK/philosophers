/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:39 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/09 15:14:39 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_death(t_data *data)
{
	int			i;
	long		current_time;
	const long	time_to_die = data->time_to_die;

	i = 0;
	current_time = get_timestamp_in_ms();
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if ((current_time - data->philos[i].last_meal) >= time_to_die)
		{
			print_mutex(&data->philos[i], "died");
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			pthread_mutex_lock(&data->doomsday_mutex);
			data->doomsday = true;
			pthread_mutex_unlock(&data->doomsday_mutex);
			return (1);
		}
		usleep(1000);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (0);
}

void	smart_usleep(long time, t_data *data)
{
	long	start;

	start = get_timestamp_in_ms();
	while (!get_doomsday(data))
	{
		if (get_timestamp_in_ms() - start >= time)
			break ;
		usleep(100);
	}
}

void	print_mutex(t_philo *philo, char *msg)
{
	long	current_time;
	long	elapsed_time;

	if (!get_doomsday(philo->data))
	{
		current_time = get_timestamp_in_ms();
		elapsed_time = current_time - philo->data->start_time;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n", elapsed_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}
