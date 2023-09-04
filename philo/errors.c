/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:10:20 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/04 14:49:17 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//careful pas le droit à exit alors make quivalent later on !

void	ft_error(char *str)
{
	printf("%s", str);
	exit(1);
}

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->data->cadenas);
	if (philo->data->locked)
	{
		pthread_mutex_unlock(philo->data->cadenas);
		return ;
	}
	printf("%ldms %d %s\n", get_current_time() - philo->thread_start,
		philo->id, str);
	pthread_mutex_unlock(philo->data->cadenas);
}

void	end_simulation_message(int check)
{
	if (!check)
		printf("Simulation ended -> everyone is alive (and full)\n");
	else
		printf("Simulation ended -> you lost a philo (RIP) \n");
}

int	check_value(t_data *data)
{
	if (data->nbr_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->meals_required == 0)
		return (1);
	else
		return (0);
}

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
