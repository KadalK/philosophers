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

long get_timestamp_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_mutex(t_philo *philo, char *msg)
{
	long	current_time;
	long	elapsed_time;

	if (!get_doomsday(philo->data))
	{
		current_time = get_timestamp_in_ms();
		elapsed_time = current_time - philo->data->start_time;

		pthread_mutex_lock(&philo->data->print_mutex);
		printf( "%ld %d %s\n", elapsed_time,  philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}
