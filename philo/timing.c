/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:41:17 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/16 16:42:48 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//FCT GET_CURRENT_TIME
// Utilise gettimeofday pour obtenir le temps actuel
// en millisecondes depuis une référence temporelle.
// Renvoie le temps actuel en millisecondes.
unsigned long long	get_current_time(void)
{
	struct timeval		time;
	unsigned long long	current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

//FCT TIME_PASSED
//permet de calculer la durée écoulée entre deux moments dans le temps.
unsigned long long	time_passed(unsigned long long start,
	unsigned long long end)
{
	return (end - start);
}

void	ft_usleep(unsigned long long time)
{
	unsigned long long int	sleep;
	unsigned long long int	current_time;

	current_time = get_current_time();
	sleep = time_passed(current_time, get_current_time());
	while (sleep < time)
	{
		sleep = time_passed(current_time, get_current_time());
		usleep(100);
	}	
}
