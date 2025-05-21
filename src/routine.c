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

void	sleep_phase(t_philo *philo)
{

	const long time_to_sleep = philo->data->time_to_sleep;
	print_mutex(philo, SLEEP);
	smart_sleep(time_to_sleep, philo->data);
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
			smart_sleep(philo->data->time_to_eat, philo->data);
	}
	return (NULL);
}
