/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/12 16:34:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_threads(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error destroying philo_thread %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		printf("Philo_thread %d exited\n", philo[i].id);
		i++;
	}
	free(philo);
	return (0);
}

int	destroy_mutex(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_destroy(&philo[i].left_fork) != 0)
		{
			printf("Error destroying mutex left_fork %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_destroy(&philo[i].right_fork) != 0)
		{
			printf("Error destroying mutex right_fork %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_destroy(&data->message) != 0)
	{
		printf("Error destroying mutex message %d\n", philo[i].id);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	time_to_die(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if ((get_current_time() - philo[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->message);
			printf("%ld %d died\n", time_passed(data->start_time,
					get_current_time()), philo->id);
			pthread_mutex_unlock(&data->message);
		}
		i++;
	}
	return (0);
}

int	we_are_full(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	if (data->meals_counter != 0)
	{
		while (i < data->nbr_philo)
		{
			if (philo[i].meals_eaten < data->meals_counter)
				return (EXIT_SUCCESS);
			i++;
		}	
		pthread_mutex_lock(&data->message);
		printf("All philos have eaten %d times\n", data->meals_counter);
		pthread_mutex_unlock(&data->message);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
