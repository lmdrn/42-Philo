/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:22 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/15 17:05:59 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_counter = ft_atoi(av[5]);
	else
		data->meals_counter = -1;
	data->cadenas = 1;
	if (pthread_mutex_init(&data->message, NULL) != 0
		|| pthread_mutex_init(&data->cadenas_mutex, NULL) != 0)
	{
		printf("There was an error during data mutex init\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

void	assign_left_fork(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < (data->nbr_philo - 1))
	{
		philo[i].left_fork = philo[i + 1].right_fork;
		i++;
	}
	philo[i].left_fork = philo[0].right_fork;
}

t_philo	*init_philo(t_data *data)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * data->nbr_philo);
	if (philo == NULL)
		return (NULL);
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].data = *data;
		philo_mutex_init(&philo[i]);
		i++;
	}
	assign_left_fork(data, philo);
	assign_threads(data, philo);
	return (philo);
}

int	philo_mutex_init(t_philo *philo)
{
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0
		|| (pthread_mutex_init(&philo->left_fork, NULL) != 0)
		|| (pthread_mutex_init(&philo->mutex_philo, NULL) != 0)
		|| (pthread_mutex_init(&philo->mutex_meal, NULL) != 0))
	{
		printf("Error creating philo mutex %d\n", philo->id);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
