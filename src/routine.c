/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:00 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/09 15:03:00 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*big_brother(void *arg)
{
	t_data	*data;

	data = (void *)arg;
	while (!get_doomsday(data))
	{
		if (check_death(data) == 1 || all_philos_meal_eaten(data))
		{
			pthread_mutex_lock(&data->doomsday_mutex);
			data->doomsday = true;
			pthread_mutex_unlock(&data->doomsday_mutex);
			break ;
		}
	}
	return (NULL);
}

bool	lonely_philo(t_data *data)
{
	if (data->nb_philo == 1)
	{
		printf("%d 1 %s\n", 0, TAKEN);
		usleep(data->time_to_die * 1000);
		printf("%ld 1 %s\n", data->time_to_die, DEAD);
		free_init(data);
		return (1);
	}
	return (0);
}

void	sleep_phase(t_philo *philo)
{
	const long	time_to_sleep = philo->data->time_to_sleep;

	print_mutex(philo, SLEEP);
	smart_usleep(time_to_sleep, philo->data);
}

void	think_phase(t_philo *philo)
{
	print_mutex(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		must_eat;

	philo = (t_philo *)arg;
	must_eat = philo->data->must_eat;
	if (philo->id % 2 == 0)
		usleep(50);
	think_phase(philo);
	while (!get_doomsday(philo->data) || philo->meals_eaten < must_eat)
	{
		if (philo->id % 2 == 0)
			usleep(50);
		eat(philo);
		sleep_phase(philo);
		think_phase(philo);
		if (philo->data->nb_philo % 2 == 1)
			smart_usleep(philo->data->time_to_eat, philo->data);
	}
	return (NULL);
}
