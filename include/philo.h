/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapinarc <kapinarc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:12:40 by kapinarc          #+#    #+#             */
/*   Updated: 2025/05/23 17:45:57 by kapinarc         ###   ########.fr       */
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

# define DEAD "is dead"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define TAKEN "has taken a fork"
# define YELLOW "\033[093m"
# define RESET "\033[039m"

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	bool			doomsday;
	long			start_time;
	bool			start;

	pthread_mutex_t	doomsday_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sleep_mutex;

	struct s_philo	*philos;
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

//----ato.c----//
long	ft_atol(const char *str);
int		ft_atoi(const char *nptr);

//----eat.c----//
bool	all_philos_meal_eaten(t_data *data);
bool	set_fork(t_fork *fork);
void	release_fork(t_fork *fork);
void	take_fork(t_philo *philo, t_fork *fork_1, t_fork *fork_2);
void	eat(t_philo *philo);

//----init.c----//
bool	init(t_data **data, char **av);
void	free_init(t_data *data);

//----main.c----//
bool	get_doomsday(t_data *data);
void	set_doomsday(t_data *data, bool value);
bool	thread_creat_n_join(t_data *data, pthread_t *thread);
bool	thread_creator(t_data *data);

//----minilib.c----//
int		ft_strlen(char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//----parse.c----//
void	error_msg(int mode);
int		valid_args(int ac, char **av);

//----routine.c----//
void	*big_brother(void *arg);
bool	lonely_philo(t_data *data);
void	sleep_phase(t_philo *philo);
void	think_phase(t_philo *philo);
void	*routine(void *arg);

//----utils.c----//
long	get_timestamp_in_ms(void);
int		check_death(t_data *data);
void	print_mutex(t_philo *philo, char *msg);
void	smart_usleep(long time, t_data *data);

#endif
