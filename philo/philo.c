/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:06:11 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/01 12:38:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if ((args_error(ac)) != 0 || (check_minmax(ac, av) != 0)
			|| (check_letters(ac, av) != 0) || (check_args(ac, av) != 0))
			return (1);
		else if (init_data(&data, ac, av) != 0)
			ft_error("Initialization error!\n");
		else if (threads_launch(&data) != 0)
			ft_error("Threads error!\n");
	}
	else
		ft_error("Args error!\n");
	return (0);
}
