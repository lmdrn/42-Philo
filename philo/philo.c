/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/17 15:56:07 by lmedrano         ###   ########.fr       */
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
	if (init_data(ac, av, &data) != 0)
	{
		printf("init data error\n");
		return (EXIT_FAILURE);
	}
	philo = init_philo(&data);
	if (philo == NULL)
	{
		printf("init philo error\n");
		return (EXIT_FAILURE);
	}
	if (faucheuse(&data, philo) != 0)
	{
		printf("faucheuse did not take any lives\n");
		return (EXIT_FAILURE);
	}
	destroy_mutex(&data, philo);
	destroy_threads(&data, philo);
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
			break ;
	}
	return (0);
}

/* int	ft_exit(t_data *data, t_philo *philo) */
/* { */
/* 	return (EXIT_FAILURE); */
/* } */
