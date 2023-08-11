/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:42:48 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 17:09:10 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	unsigned int	i;

	i = 0;
	philo = (t_philo *)arg;
	data = &philo->data;
	if (check_all_alive(data, philo) == 0)
	{
		while (i < data->nbr_philo)
		{
			if ((philo[i].id % 2) == 0)
				ft_usleep(500);
			else
			{
				if (check_all_alive(data, philo) == 0)
					printf("forks action\n");
				if (check_all_alive(data, philo) == 0)
					printf("eat action\n");
				if (check_all_alive(data, philo) == 0)
					printf("sleep action\n");
				if (check_all_alive(data, philo) == 0)
					printf("think action\n");
				if (check_all_alive(data, philo) == 0)
					printf("dead action\n");
			}
			i++;
		}
	}
	return (0);
}

void	philo_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&data->message);
	printf("%ld %d has taken a fork\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_lock(&philo->right_fork);
	printf("%ld %d has taken a fork\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_unlock(&data->message);
}

void	philo_eats(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->message);
	printf("%ld %d is eating\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_unlock(&data->message);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	philo->last_meal = data->time_to_eat + time_passed(data->start_time,
			get_current_time());
	philo->meals_eaten += 1;
}

void	philo_thinks(t_data *data, t_philo *philo)
{
	ft_usleep(time_passed(data->start_time, get_current_time())
		+ data->time_to_sleep);
	pthread_mutex_lock(&data->message);
	printf("%ld %d is thinking\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_unlock(&data->message);
}

void	is_dead(t_data *data, t_philo *philo)
{
	ft_usleep(philo->last_meal + data->time_to_die);
	pthread_mutex_lock(&data->message);
	printf("%ld %d died\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	if (data->meals_counter < data->nbr_philo)
		philo->is_alive = 0;
	pthread_mutex_unlock(&data->message);
	ft_usleep(data->time_to_die);
	free(philo);
	destroy_threads(data, philo);
	destroy_mutex(data, philo);
}
