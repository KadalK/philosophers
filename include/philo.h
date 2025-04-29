/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:12:40 by kapinarc          #+#    #+#             */
/*   Updated: 2025/04/25 20:20:30 by kapinarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>


typedef struct s_data
{
	int		nb_philo;
	long 	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat;
	bool	doomsday;
	long	start_time;
	bool	start;

	pthread_mutex_t	*forks;



	struct	s_philo *philos;
} t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}			t_philo;

//----minilib.c----//
int		ft_atoi(const char *nptr);
long	ft_atol(const char *str);
int		ft_isdigit(int c);

//----parse.c----//
int	valid_args(int ac, char **av);

//----init.c----//
bool	init(t_data **data, char **av);


#endif
