/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:24:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 13:40:26 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_error(int ac)
{
	if (ac == 1)
	{
		printf("No args wtf ?!\n");
		return (EXIT_FAILURE);
	}
	if (ac > 6)
	{
		printf("Too many args\n");
		return (EXIT_FAILURE);
	}
	if (ac < 5)
	{
		printf("Too few args\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	check_minmax(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < -2147483648 || ft_atoi(av[i]) > 2147483647)
		{
			printf("Int overflow\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

int	check_letters(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0')
			{
				printf("Not a positive number\n");
				return (EXIT_FAILURE);
			}
			if (av[i][j] > '9')
			{
				printf("Not a number\n");
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int			i;
	long int	arg;

	i = 0;
	while (i < ac)
	{
		arg = ft_atoi(av[i]);
		if (i == 1 && arg < 1)
		{
			printf("There should be at least 1 philo bro\n");
			return (EXIT_FAILURE);
		}
		if (i == 1 && arg > 200)
		{
			printf("Too much philos, not enough actions\n");
			return (EXIT_FAILURE);
		}
		if ((i == 2 || i == 3 || i == 4) && arg < 60)
		{
			printf("Nothing happens below 60ms mate...\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}
