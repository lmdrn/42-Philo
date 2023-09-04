/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:00:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 13:33:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_die(t_data *data, t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(data->cadenas);
	time = get_current_time() - philo->meal_time;
	if (time >= data->time_to_die)
	{
		pthread_mutex_unlock(data->cadenas);
		philo_dies(philo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(data->cadenas);
		return (0);
	}
}

int	we_are_full(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(philo->data->cadenas);
	if (data->meals_current == 1 && i == data->nbr_philo - 1
		&& data->meals_required == philo->meals_eaten)
	{
		pthread_mutex_unlock(philo->data->cadenas);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->data->cadenas);
		return (0);
	}
}
