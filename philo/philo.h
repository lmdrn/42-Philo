/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:06:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 17:09:13 by lmedrano         ###   ########.fr       */
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
	unsigned int	nbr_philo;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	unsigned int	meals_counter;
	int				all_alive;
	int				all_eaten;
	pthread_mutex_t	message;
	long long int	start_time;
}	t_data;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	unsigned int	meals_eaten;
	int				is_alive;
	int				last_meal;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	t_data			data;
}	t_philo;

/* ooo ----- ooo PROTOS ooo ----- ooo */

int				ft_isspace(char c);
long long int	ft_atoi(const char *str);
int				ft_isdigit(int c);
int				args_error(int ac);
int				check_minmax(int ac, char **av);
int				check_args(int ac, char **av);
int				check_letters(int ac, char **av);
int				init_data(int ac, char **av, t_data *data);
t_philo			*init_philo(t_data *data);
void			start_timer(t_data *data);
long int		get_current_time(void);
long int		time_passed(long int start, long int end);
long int		ft_usleep(long int time);
int				assign_threads(t_data *data, t_philo *philo);
int				check_all_alive(t_data *data, t_philo *philo);
void			*routine(void *arg);
int				destroy_threads(t_data *data, t_philo *philo);
int				destroy_mutex(t_data *data, t_philo *philo);

#endif
