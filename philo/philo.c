/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/12 16:34:36 by lmedrano         ###   ########.fr       */
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
	philo = init_philo(&data);
	if (init_data(ac, av, &data) != 0)
		destroy_mutex(&data, philo);
	if (philo != 0)
	{
		destroy_mutex(&data, philo);
		destroy_threads(&data, philo);
	}
	faucheuse(&data, philo);
	destroy_mutex(&data, philo);
	destroy_threads(&data, philo);
	return (0);
}

void	faucheuse(t_data *data, t_philo *philo)
{
	while (1)
	{
		if (time_to_die(data, philo) == 1)
			break ;
		else if (we_are_full(data, philo) == 1)
			break ;
	}
}
