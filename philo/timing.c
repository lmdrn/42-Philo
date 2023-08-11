/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:41:17 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/11 15:46:22 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_timer(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec * 1000);
}

long int	get_current_time(void)
{
	struct timeval	time;
	long int		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec * 1000);
	return (current_time);
}

long int	time_passed(long int start, long int end)
{
	return (end - start);
}

long int	ft_usleep(long int time)
{
	long int	sleep;

	sleep = ((get_current_time() + time) / 1000);
	while (get_current_time() < sleep)
		usleep(100);
	return (sleep);
}
