/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:42:48 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/12 16:26:23 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = &philo->data;
	if (philo->id % 2 != 0)
		usleep(500);
	while (check_all_alive(data))
	{
		if (check_all_alive(data) != 0)
			philo_forks(data, philo);
		if (check_all_alive(data) != 0)
			philo_eats(data, philo);
		if (check_all_alive(data) != 0)
			philo_sleeps(data, philo);
		if (check_all_alive(data) != 0)
			philo_thinks(data, philo);
	}
	return (0);
}

void	philo_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&data->message);
	printf("%ld %d has taken a fork\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_lock(&philo->left_fork);
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
	philo->last_meal = get_current_time();
	philo->meals_eaten += 1;
	if (philo->meals_eaten == data->meals_counter)
		data->all_eaten += 1;
}

void	philo_sleeps(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->message);
	printf("%ld %d is sleeping\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_unlock(&data->message);
	ft_usleep(data->time_to_sleep);
}

void	philo_thinks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->message);
	printf("%ld %d is thinking\n", time_passed(data->start_time,
			get_current_time()), philo->id);
	pthread_mutex_unlock(&data->message);
}
