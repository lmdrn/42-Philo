/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/16 13:18:51 by lmedrano         ###   ########.fr       */
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

// FCT FAUCHEUSE
// Crée une boucle infinie qui vérifie continuellement
// les conditions de fin de simulation 
// à l'aide des fonctions time_to_die et we_are_full.
// S'arrête dès qu'une de ces conditions est remplie.
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
