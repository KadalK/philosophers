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

long get_timestamp_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int check_death(t_data *data)
{
	int	i;

	i = 0;
	long current_time = get_timestamp_in_ms();
	while (i < data->nb_philo)
	{
		if ((current_time - data->philos[i].last_meal) == data->time_to_die)
		{
			printf("Jai faim ! | Philo number : %d died.\n", data->philos[i].id);
		}
		if ((current_time - data->philos[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("time of death : %ld | Philo number : %d died.\n", current_time , data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*big_brother(void *arg)
{
	t_data *data;
	data = (void *)arg;
	while(data->doomsday != true)
	{
		if (check_death(data) == 1)
		{
			data->doomsday = true;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_timestamp_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	while (philo->data->doomsday != true)
	{
		printf("Le philo %d dit : NTM.\n", philo->id);
		philo->last_meal = get_timestamp_in_ms();
	}
	return (NULL);
}

bool	thread_creat_n_join(t_data *data, pthread_t *thread)
{
	int i;
	pthread_t supervisor;

	i = 0;
	while (i < data->nb_philo)
	{
		printf("DEBUG %d\n", i);
		if (pthread_create(&thread[i], NULL, routine, &data->philos[i]) != 0)
		{
			perror("creat pthread failed\n");
			return (false);
		}
		i++;
	}
		if (pthread_create(&supervisor, NULL, big_brother, data) != 0)
		{
			perror("creat supervisor failed\n");
			return (false);
		}
	i = 0;
	while ( i < data->nb_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("join pthread failed\n");
			return (false);
		}
		i++;
	}
	if (pthread_join(supervisor, NULL) != 0)
	{
		perror("join supervisor failed\n");
		return (false);
	}
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
	printf("DEBUG nb_philo = %d\n", data->nb_philo);
	thread_creator(data);
	return (0);
}