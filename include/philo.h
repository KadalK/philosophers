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

# define DEAD "KK"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define TAKEN "has taken a fork"
# define YELLOW "\033[093m"
# define RESET "\033[039m"

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

	pthread_mutex_t	doomsday_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sleep_mutex;

	struct	s_philo	*philos;
	struct s_fork	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;

	struct s_fork	*l_fork;
	struct s_fork	*r_fork;

	pthread_t		thread;
	pthread_mutex_t	meal_mutex;

	t_data			*data;
}			t_philo;

typedef struct s_fork
{
	bool			available;
	pthread_mutex_t	fork;
}			t_fork;

//----not define---//
bool	get_doomsday(t_data *data);
int check_death(t_data *data);

//----routine.c----//
void	*routine(void *arg);
void	*big_brother(void *arg);

//----utils.c----//
long get_timestamp_in_ms(void);
void print_mutex(t_philo *philo, char *msg);

//----minilib.c----//
int		ft_atoi(const char *nptr);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int	ft_isalpha(int c);
void	ft_putendl_fd(char *s, int fd);

//----parse.c----//
int	valid_args(int ac, char **av);

//----init.c----//
bool	init(t_data **data, char **av);
void	free_init(t_data *data);

//----eat.c----//
void	eat(t_philo *philo);

#endif
