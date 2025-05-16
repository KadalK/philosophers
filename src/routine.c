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

void	smart_sleep(t_data *data, long duration)
{
	long	start_time = get_timestamp_in_ms();
	while(!get_doomsday(data))
	{
		if (get_timestamp_in_ms() - start_time >= duration)
			break ;
		usleep(50);
	}
}

void	sleep_phase(t_philo *philo)
{

	const long time_to_sleep = philo->data->time_to_sleep;
	smart_sleep(philo->data, time_to_sleep);
	print_mutex(philo, SLEEP);
}

void	think_phase(t_philo *philo)
{
	print_mutex(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_doomsday(philo->data))
	{
		eat(philo);
		sleep_phase(philo);
		think_phase(philo);
	}
	return (NULL);
}
