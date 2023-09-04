/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:38:23 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 14:56:32 by lmedrano         ###   ########.fr       */
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
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nbr_philo)
	{
		philo[i].thread_start = data->start_time;
		philo[i].meal_time = data->start_time;
		i++;
	}
	i = 0;
	if (data->nbr_philo == 1)
	{
		one_philo(data);
		return (0);
	}
	while (i < data->nbr_philo)
	{
		philo[i].right_fork = philo[(i + 1) % data->nbr_philo].left_fork;
		if (pthread_create(&philo[i].thread, NULL, &routine,
				&philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	faucheuse(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->locked)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			if (time_to_die(data, philo) || we_are_full(data, philo, i))
			{
				pthread_mutex_lock(philo->data->cadenas);
				philo->data->locked = 1;
				pthread_mutex_unlock(philo->data->cadenas);
			}
			i++;
		}
	}
	pthread_mutex_lock(philo->data->cadenas);
	if (philo[i].meals_eaten < data->meals_required && data->nbr_philo != 1 )
	{
		pthread_mutex_unlock(philo->data->cadenas);
		ft_usleep(500);
		printf("All philos have eaten %d times\n", data->meals_required);
		return (0);
	}
	pthread_mutex_unlock(philo->data->cadenas);
	return (1);
}

void	end_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(philo[i].thread, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(data->cadenas);
	free(data->forks);
	free(data->cadenas);
	free(philo);
}

int	threads_launch(t_data *data)
{
	t_philo	*philo;
	int		check;

	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo || init_philo(data, philo) != 0)
		ft_error("Init philo error\n");
	if (assign_threads(data, philo) != 0)
		return (1);
	check = faucheuse(data, philo);
	end_simulation_message(check);
	end_simulation(data, philo);
	return (0);
}
