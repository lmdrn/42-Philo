/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:24:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/02 18:03:39 by lmedrano         ###   ########.fr       */
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

int	check_minmax(int arg)
{
	if (arg < -2147483648 || arg > 2147483647)
	{
		printf("below INT_MIN OR above INT_MAX\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	check_neg(int arg)
{
	if (arg < 0)
	{
		printf("Please do not put negative numbers\n");
		return (EXIT_FAILURE);
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
		check_neg(arg);
		check_minmax(arg);
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

int	main(int ac, char **av)
{
	if (args_error(ac) == 0)
		check_args(ac, av);
}
