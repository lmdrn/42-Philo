/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 15:38:27 by lmedrano         ###   ########.fr       */
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
