/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:59:27 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 15:29:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "string.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "sys/time.h"
# include "pthread.h"

/* xx -- STRUCTURES -- xx */

typedef struct s_data {
	int		nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_required;
	int		meals_current;
	int		locked;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*cadenas;
}	t_data;

typedef struct s_philo {
	int		id;
	int		dead;
	int		meals_eaten;
	long int	thread_start;
	long int	meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

/* xx -- PROTOTYPES DE FUNCTIONS -- xx */

/* xx -- UTILS -- xx */

int		ft_isspace(char c);
long long int	ft_atoi(const char *str);
int		ft_isdigit(int c);

/* xx -- ARGS -- xx */

int		ft_error(char *str);
int		args_error(int ac);
int		check_minmax(int ac, char **av);
int		check_letters(int ac, char **av);
int		check_args(int ac, char **av);

/* xx -- INIT -- xx */

int		init_data(t_data *data, int ac, char **av);
int		init_mutex(t_data *data);
int		init_philo(t_data *data, t_philo *philo);

/* xx -- TIMING -- xx */

long	int	get_current_time(void);
void	ft_usleep(long int time);

/* xx -- THREADS -- xx */

int		assign_threads(t_data *data, t_philo *philo);
void	end_simulation(t_data *data, t_philo *philo);
int		threads_launch(t_data *data);

/* xx -- ROUTINE -- xx */

void	*routine(void *arg);
void	message(char *str, t_philo *philo);
void	philo_eats(t_philo *philo);
void	philo_sleeps(t_philo *philo);
void	philo_thinks(t_philo *philo);
void	philo_dies(t_philo *philo);

/* xx -- CHECKS -- xx */

int		time_to_die(t_data *data, t_philo *philo);
int		we_are_full(t_data *data, t_philo *philo, int i);
int		faucheuse(t_data *data, t_philo *philo);
int		bellies_full(int i, t_data *data, t_philo *philo);

/* xx -- MESSAGES -- xx */

void	message(char *str, t_philo *philo);
void	end_simulation_message(int check);

#endif
