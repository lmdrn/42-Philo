/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:17:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 14:33:01 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = -2;
	data->meals_current = 0;
	data->start_time = 0;
	data->locked = 0;
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		data->meals_current = 1;
	}
	if (init_mutex(data) != 0)
		ft_error("Mutex init error\n");
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = 0;
	data->cadenas = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		return (1);
	data->cadenas = malloc(sizeof(pthread_mutex_t));
	if (!data->cadenas)
		return (1);
	if (pthread_mutex_init(data->cadenas, NULL) != 0)
		ft_error("mutex init error\n");
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			ft_error("mutex init error\n");
		i++;
	}
	return (0);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].meal_time = 0;
		philo[i].meals_eaten = 0;
		philo[i].thread_start = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = 0;
		philo[i].data = data;
		i++;
	}
	return (0);
}
