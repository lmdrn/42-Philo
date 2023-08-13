/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:41:17 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/13 18:12:51 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_current_time(void)
{
	struct timeval	time;
	long int		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

long int	time_passed(long int start, long int end)
{
	return (end - start);
}

void	ft_usleep(long int time)
{
	long int	sleep;
	long int	current_time;

	current_time = get_current_time();
	sleep = time_passed(current_time, get_current_time());
	while (sleep < time)
	{
		sleep = time_passed(current_time, get_current_time());
		usleep(1000);
	}	
}
