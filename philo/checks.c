/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:00:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 15:25:59 by lmedrano         ###   ########.fr       */
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

int	faucheuse(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->locked)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			if (time_to_die(data, philo) || we_are_full(data, philo, i))
			{
				pthread_mutex_lock(philo->data->cadenas);
				philo->data->locked = 1;
				pthread_mutex_unlock(philo->data->cadenas);
			}
			i++;
		}
	}
	pthread_mutex_lock(philo->data->cadenas);
	bellies_full(i, data, philo);
	pthread_mutex_unlock(philo->data->cadenas);
	return (1);
}

int	bellies_full(int i, t_data *data, t_philo *philo)
{
	if (philo[i].meals_eaten < data->meals_required && data->nbr_philo != 1)
	{
		pthread_mutex_unlock(philo->data->cadenas);
		ft_usleep(500);
		printf("All philos have eaten %d times\n", data->meals_required);
		return (0);
	}
	return (1);
}
