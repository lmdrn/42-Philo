/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/23 15:08:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Error destroying philo_thread %d\n", data->philo[i].id);
			return (1);
		}
		printf("Philo_thread %d exited\n", data->philo[i].id);
		i++;
	}
	return (0);
}

void	free_the_philo(t_data *data)
{
	free(data->philo);
}

int	destroy_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_destroy(&data->philo[i].right_fork) != 0)
			printf("could not destroy right fork\n");
		i++;
	}
	if (pthread_mutex_destroy(&data->message) != 0)
		printf("could not destroy message\n");
	if (pthread_mutex_destroy(&data->cadenas_mutex) != 0)
		printf("could not destroy mutex\n");
	if (pthread_mutex_destroy(&data->philo->mutex_meal) != 0)
		printf("could not destroy mutex\n");
	if (pthread_mutex_destroy(&data->philo->mutex_lastmeal) != 0)
		printf("could not destroy mutex\n");
	return (0);
}

// FCT TIME_TO_DIE
// Vérifie si le temps écoulé depuis le dernier repas d'un philosophe
// est supérieur ou égal à data->time_to_die.
//Si c'est le cas, elle déclare ce philosophe mort,
// désactive le cadenas et imprime un message.
unsigned int	time_to_die(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->philo[i].mutex_lastmeal);
		if ((get_current_time() - data->philo[i].last_meal)
			>= data->time_to_die)
		{
			pthread_mutex_lock(&data->cadenas_mutex);
			data->cadenas = 0;
			pthread_mutex_unlock(&data->cadenas_mutex);
			pthread_mutex_lock(&data->message);
			printf("%llu %d died\n", time_passed(data->start_time,
					get_current_time()), data->philo->id);
			pthread_mutex_unlock(&data->message);
			pthread_mutex_unlock(&data->philo[i].mutex_lastmeal);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].mutex_lastmeal);
		i++;
	}
	return (0);
}

//FCT WE_ARE_FULL
//érifie si tous les philosophes ont mangé le nombre de repas requis
// (data->meals_counter) en parcourant tous les philosophes. 
//Si c'est le cas, elle désactive le cadenas
// et imprime un message indiquant que tous les philosophes ont fini de manger.
int	we_are_full(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (data->meals_counter != -1)
	{
		while (i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->philo[i].mutex_meal);
			if (data->philo[i].meals_eaten < data->meals_counter)
			{
				pthread_mutex_unlock(&data->philo[i].mutex_meal);
				return (0);
			}
			pthread_mutex_unlock(&data->philo[i].mutex_meal);
			i++;
		}
		pthread_mutex_lock(&data->cadenas_mutex);
			data->cadenas = 0;
		pthread_mutex_unlock(&data->cadenas_mutex);
		pthread_mutex_lock(&data->message);
		printf("All philos have eaten %d times\n", data->meals_counter);
		pthread_mutex_unlock(&data->message);
		return (1);
	}
	return (0);
}
