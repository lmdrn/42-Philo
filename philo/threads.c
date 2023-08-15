/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:11:15 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/15 17:22:06 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	return (0);
}

int	assign_threads(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			printf("Error creating philo_thread %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_cadenas(t_data *data)
{
	pthread_mutex_lock(&data->cadenas_mutex);
	if (data->cadenas == 1)
	{
		pthread_mutex_unlock(&data->cadenas_mutex);
		return (EXIT_FAILURE);
	}
	else
	{
		pthread_mutex_unlock(&data->cadenas_mutex);
		return (EXIT_SUCCESS);
	}
}
