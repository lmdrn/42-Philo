/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/15 16:06:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if ((args_error(ac)) && (check_minmax(ac, av)) && (check_letters(ac, av))
		&& (check_args(ac, av)))
	{
		printf("Args error\n");
		return (EXIT_FAILURE);
	}
	init_data(ac, av, &data);
	philo = init_philo(&data);
	if (faucheuse(&data, philo) != 0)
	{
		destroy_mutex(&data, philo);
		destroy_threads(&data, philo);
	}
	return (0);
}

int	faucheuse(t_data *data, t_philo *philo)
{
	while (1)
	{
		if ((time_to_die(data, philo) != 0) || (we_are_full(data, philo) != 0))
		{
			break ;
		}
	}
	return (EXIT_SUCCESS);
}
