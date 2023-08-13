/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:22 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/13 18:42:31 by lmedrano         ###   ########.fr       */
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
	data->all_alive = 1;
	data->all_eaten = 0;
	if (pthread_mutex_init(&data->message, NULL) != 0)
	{
		printf("There was an error during message mutex init\n");
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
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (philo == NULL)
		return (NULL);
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].is_alive = 1;
		philo[i].last_meal = get_current_time();
		if (pthread_mutex_init(&philo[i].right_fork, NULL) != 0)
		{
			printf("Error creating right_fork philo %d\n", philo[i].id);
			return (NULL);
		}
		if (pthread_mutex_init(&philo[i].left_fork, NULL) != 0)
		{
			printf("Error creating left_fork philo %d\n", philo[i].id);
			return (NULL);
		}
		philo[i].data = *data;
		i++;
	}
	assign_left_fork(data, philo);
	assign_threads(data, philo);
	return (philo);
}
