/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/15 17:22:07 by lmedrano         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

int	destroy_mutex(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_destroy(&philo[i].left_fork) != 0)
			printf("could not destroy left fork\n");
		if (pthread_mutex_destroy(&philo[i].right_fork) != 0)
			printf("could not destroy right fork\n");
		if (pthread_mutex_destroy(&philo[i].mutex_philo) != 0)
			printf("could not destroy mutex philo\n");
		if (pthread_mutex_destroy(&philo[i].mutex_meal) != 0)
			printf("could not destroy mutex meal\n");
		i++;
	}
	if (pthread_mutex_destroy(&data->message) != 0)
		printf("could not destroy message\n");
	if (pthread_mutex_destroy(&data->cadenas_mutex) != 0)
		printf("could not destroy mutex\n");
	return (0);
}

unsigned int	time_to_die(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_philo);
		if ((get_current_time() - philo[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->cadenas_mutex);
			data->cadenas = 0;
			pthread_mutex_unlock(&data->cadenas_mutex);
			pthread_mutex_lock(&data->message);
			printf("%ld %d died\n", time_passed(data->start_time,
					get_current_time()), philo->id);
			pthread_mutex_unlock(&data->message);
			pthread_mutex_unlock(&philo[i].mutex_philo);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&philo[i].mutex_philo);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	we_are_full(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	if (data->meals_counter != -1)
	{
		while (i < data->nbr_philo)
		{
			pthread_mutex_lock(&philo[i].mutex_meal);
			if (philo[i].meals_eaten < data->meals_counter)
			{
				pthread_mutex_unlock(&philo[i].mutex_meal);
				return (EXIT_SUCCESS);
			}
			pthread_mutex_unlock(&philo[i].mutex_meal);
			i++;
		}
		pthread_mutex_lock(&data->cadenas_mutex);
		data->cadenas = 0;
		pthread_mutex_lock(&data->message);
		printf("All philos have eaten %d times\n", data->meals_counter);
		pthread_mutex_unlock(&data->message);
		pthread_mutex_unlock(&data->cadenas_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
