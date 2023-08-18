/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/18 22:19:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if ((args_error(ac)) && (check_minmax(ac, av)) && (check_letters(ac, av))
		&& (check_args(ac, av)))
	{
		printf("Args error\n");
		return (EXIT_FAILURE);
	}
	if (init_data(ac, av, &data) != 0)
		ft_exit("Init data error\n", &data);
	if (init_philo(&data) != 0)
		ft_exit("Init philo error\n", &data);
	if (faucheuse(&data) != 0)
		ft_exit("faucheuse did not take any lives\n", &data);
	ft_exit("Threads exited, mutexes destroyed and philos freed\n", &data);
	return (0);
}

int	ft_exit(char *str, t_data *data)
{
	printf("%s\n", str);
	destroy_mutex(data);
	destroy_threads(data);
	free_the_philo(data);
	return (EXIT_FAILURE);
}

// FCT FAUCHEUSE
// Crée une boucle infinie qui vérifie continuellement
// les conditions de fin de simulation 
// à l'aide des fonctions time_to_die et we_are_full.
// S'arrête dès qu'une de ces conditions est remplie.
int	faucheuse(t_data *data)
{
	while (1)
	{
		if ((time_to_die(data) != 0) || (we_are_full(data) != 0))
			break ;
	}
	return (0);
}
