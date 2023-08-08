/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:22 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/08 19:00:32 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_timer(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec * 1000);
}

int	init_data(int ac, char **av)
{
	t_data			data;
	long int		arg;

	arg = ft_atoi(av[2]);
	printf("%ld\n", arg);
	data.nbr_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.meals_counter = ft_atoi(av[5]);
	data.all_alive = 1;
	if (pthread_mutex_init(data.message, NULL) != 0)
	{
		printf("There was an error during message mutex init\n");
		return (EXIT_FAILURE);
	}
	start_timer(&data);
	return (0);
}
