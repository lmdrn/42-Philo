/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:07:50 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 15:26:16 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	pthread_mutex_lock(philo->data->cadenas);
	while (!philo->data->locked)
	{
		pthread_mutex_unlock(philo->data->cadenas);
		philo_eats(philo);
		philo_sleeps(philo);
		pthread_mutex_lock(philo->data->cadenas);
	}
	pthread_mutex_unlock(philo->data->cadenas);
	return (NULL);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->data->cadenas);
	philo->meal_time = get_current_time();
	pthread_mutex_unlock(philo->data->cadenas);
	ft_usleep(philo->data->time_to_eat);
	message("is eating", philo);
	pthread_mutex_lock(philo->data->cadenas);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->cadenas);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleeps(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep);
	message("is sleeping", philo);
	philo_thinks(philo);
}

void	philo_thinks(t_philo *philo)
{
	message("is thinking", philo);
}

void	philo_dies(t_philo *philo)
{
	message("died †", philo);
	philo->dead = 1;
	pthread_mutex_lock(philo->data->cadenas);
	philo->data->locked = 1;
	pthread_mutex_unlock(philo->data->cadenas);
}
