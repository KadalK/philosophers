/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_ideas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:03:03 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/08 14:22:09 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->doomsday_mutex);
		while(philo->data->doomsday != true)
		{
			pthread_mutex_unlock(&philo->data->doomsday_mutex);
			pthread_mutex_lock(&philo->right_fork->fork);
			if (philo->right_fork->dispo == true)
			{
				philo->right_fork->dispo = false;
				pthread_mutex_unlock(&philo->right_fork->fork);			//ici les philo pair recup la fourchette droite
				break ;
			}
			pthread_mutex_unlock(&philo->right_fork->fork);
			usleep(100);
		}
	}
	else if (philo->id % 1 == 0)
	{
		pthread_mutex_lock(&philo->data->doomsday_mutex);
		while(philo->data->doomsday != true)
		{
			pthread_mutex_unlock(&philo->data->doomsday_mutex);
			pthread_mutex_lock(&philo->left_fork->fork);
			if (philo->left_fork->dispo == true)
			{
				philo->left_fork->dispo = false;
				pthread_mutex_unlock(&philo->left_fork->fork);			//ici les philos impair recup la fouchette gauche
				break ;
			}
			pthread_mutex_unlock(&philo->left_fork->fork);
			usleep(100);
		}
	}
	if (philo->id)										//peu importe le philo
	{
		pthread_mutex_lock(&philo->data->doomsday_mutex);
		while(philo->data->doomsday != true)
		{
			pthread_mutex_unlock(&philo->data->doomsday_mutex);
			pthread_mutex_lock(&philo->left_fork->fork);
			if (philo->id % 2 == 0 && philo->left_fork->dispo == true)			//philo pair
			{
				philo->left_fork->dispo = false;
				pthread_mutex_unlock(&philo->left_fork->fork);
				break ;
			}
			pthread_mutex_lock(&philo->left_fork->fork);
			if (philo->id % 1 == 0 && philo->right_fork->dispo == true)
			{
				philo->right_fork->dispo = false;
				pthread_mutex_unlock(&philo->left_fork->fork);
				break ;
			}
			pthread_mutex_unlock(&philo->left_fork->fork);
			usleep(100);
		}
		print_mutex(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		philo->meals_eaten++;

		pthread_mutex_lock(&philo->left_fork->fork);
		philo->left_fork->dispo = true;
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_lock(&philo->right_fork->fork);
		philo->right_fork->dispo = true;
		pthread_mutex_unlock(&philo->left_fork->fork);
		philo->last_meal = get_timestamp_in_ms();
	}
}


---------------------------------------------------------------------------------------------------

bool	set_fork(t_fork *fork)
{
	bool succes;

	succes = false;
	pthread_mutex_lock(&fork->fork);
	if (fork->available)
	{
		fork->available = false;
		succes = true;
	}
	pthread_mutex_unlock(&fork->fork);
	return (succes);
}

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->available = true;
	pthread_mutex_unlock(&fork->fork);
}

bool	take_fork(t_philo *philo, t_fork *fork_1, t_fork *fork_2)
{
	if (set_fork(fork_1))
	{
		print_mutex(philo, TAKEN);
		if (set_fork(fork_2))
		{
			print_mutex(philo, TAKEN);
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = get_timestamp_in_ms();
			pthread_mutex_unlock(&philo->meal_mutex);
			print_mutex(philo, EAT);
			usleep(philo->data->time_to_eat * 1000);
			release_fork(fork_2);
			release_fork(fork_1);
			return (true);
		}
		release_fork(fork_1);
	}
	return (false);
}

void	eat(t_philo *philo)
{
	while (!get_doomsday(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			if (!take_fork(philo, philo->l_fork, philo->r_fork))
				usleep(100);
		}
		else
		{
			if (!take_fork(philo, philo->r_fork, philo->l_fork))
				usleep(100);
		}
	}
}