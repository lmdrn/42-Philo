/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:06:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/29 17:20:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

/* ooo ----- ooo STRUCTS ooo ----- ooo */

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			thread;
	int					meals_eaten;
	unsigned long long	last_meal;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		mutex_meal;
	pthread_mutex_t		mutex_lastmeal;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	unsigned int		nbr_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					meals_counter;
	pthread_mutex_t		message;
	long long int		start_time;
	pthread_mutex_t		cadenas_mutex;
	int					cadenas;
	t_philo				*philo;
}	t_data;

/* ooo ----- ooo PROTOS ooo ----- ooo */

int						ft_isspace(char c);
long long int			ft_atoi(const char *str);
int						ft_isdigit(int c);
int						args_error(int ac);
int						check_minmax(int ac, char **av);
int						check_args(int ac, char **av);
int						check_letters(int ac, char **av);
int						init_data(int ac, char **av, t_data *data);
int						init_philo(t_data *data);
unsigned long long		get_current_time(void);
unsigned long long		time_passed(unsigned long long start,
							unsigned long long end);
void					ft_usleep(unsigned long long time);
int						one_philo(t_data *data);
int						assign_threads(t_data *data);
int						check_cadenas(t_philo *philo);
void					*routine(void *arg);
void					philo_forks(t_philo *philo);
void					philo_eats(t_philo *philo);
void					philo_sleeps(t_philo *philo);
void					philo_thinks(t_philo *philo);
int						faucheuse(t_data *data);
unsigned int			time_to_die(t_data *data);
int						we_are_full(t_data *data);
int						destroy_threads(t_data *data);
int						destroy_mutex(t_data *data);
int						ft_exit(char *str, t_data *data);
void					free_the_philo(t_data *data);

#endif
