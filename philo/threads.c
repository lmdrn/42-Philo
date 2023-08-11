/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:11:15 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 15:57:30 by lmedrano         ###   ########.fr       */
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

int	check_all_alive(t_data *data, t_philo *philo)
{
	if ((data->meals_counter < data->nbr_philo) && (philo->is_alive == 1)
		&& ((data->time_to_sleep + data->time_to_eat) < data->time_to_die))
		return (0);
	return (1);
}
