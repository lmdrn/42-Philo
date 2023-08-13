/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:11:15 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/13 18:05:48 by lmedrano         ###   ########.fr       */
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
	if (data->nbr_philo == 1)
		one_philo(data);
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			printf("Error creating philo_thread %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

int	check_all_alive(t_data *data)
{
	if ((data->all_alive == 1) && ((data->meals_counter == 0)
			|| (data->all_eaten < data->nbr_philo)))
		return (0);
	return (1);
}
