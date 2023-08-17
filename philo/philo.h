/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:06:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/17 17:38:33 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

/* ooo ----- ooo STRUCTS ooo ----- ooo */

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
	pthread_mutex_t		mutex_meal; // use general mutex to modify shared variables into philo
	pthread_mutex_t		mutex_lastmeal; // use general mutex to modify shared variables into philo
	int					cadenas;
}	t_data;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			thread;
	int					meals_eaten;
	unsigned long long	last_meal;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	t_data				data;
}	t_philo;

/* ooo ----- ooo PROTOS ooo ----- ooo */

int						ft_isspace(char c);
long long int			ft_atoi(const char *str);
int						ft_isdigit(int c);
int						args_error(int ac);
int						check_minmax(int ac, char **av);
int						check_args(int ac, char **av);
int						check_letters(int ac, char **av);
int						init_data(int ac, char **av, t_data *data);
t_philo					*init_philo(t_data *data);
int						philo_mutex_init(t_philo *philo);
unsigned long long		get_current_time(void);
unsigned long long		time_passed(unsigned long long start,
							unsigned long long end);
void					ft_usleep(unsigned long long time);
void					start_timer(t_data *data);
int						one_philo(t_data *data);
int						assign_threads(t_data *data, t_philo *philo);
int						check_cadenas(t_data *data);
void					*routine(void *arg);
void					philo_forks(t_data *data, t_philo *philo);
void					philo_eats(t_data *data, t_philo *philo);
void					philo_sleeps(t_data *data, t_philo *philo);
void					philo_thinks(t_data *data, t_philo *philo);
int						faucheuse(t_data *data, t_philo *philo);
unsigned int			time_to_die(t_data *data, t_philo *philo);
int						we_are_full(t_data *data, t_philo *philo);
int						destroy_threads(t_data *data, t_philo *philo);
int						destroy_mutex(t_data *data, t_philo *philo);
/* int						ft_exit(t_data *data, t_philo *philo); */
/* void					print_message(t_data *data, t_philo *philo, */
							/* char *message); */

#endif
