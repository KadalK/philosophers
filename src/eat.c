/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:04:16 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/08 14:22:47 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	set_fork(t_fork *fork)
{
	bool success;

	success = false;
	pthread_mutex_lock(&fork->fork);
	if (fork->available)
	{
		fork->available = false;
		success = true;
	}
	pthread_mutex_unlock(&fork->fork);
	return (success);
}

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->available = true;
	pthread_mutex_unlock(&fork->fork);
}

void	take_fork(t_philo *philo, t_fork *fork_1, t_fork *fork_2)
{
	if (set_fork(fork_1))
	{
		print_mutex(philo, TAKEN);
		if (set_fork(fork_2))
		{
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = get_timestamp_in_ms();
			pthread_mutex_unlock(&philo->meal_mutex);
			print_mutex(philo, TAKEN);
			print_mutex(philo, EAT);
			usleep(philo->data->time_to_eat);
			release_fork(fork_2);
			release_fork(fork_1);
			//TODO mutex meal
			philo->meals_eaten++;
		}
		release_fork(fork_1);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_fork(philo, philo->r_fork, philo->l_fork);
	}
	else
	{
		take_fork(philo, philo->l_fork, philo->r_fork);
	}

	usleep(50);
}
