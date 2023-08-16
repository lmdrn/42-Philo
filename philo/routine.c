/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:06:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/16 13:21:21 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//FCT ROUTINE
//Gère le cas où il y a un seul philosophe avec one_philo.
//Sinon, Effectue le cycle "prendre une fourchette - manger - dormir - penser"
// tant que le verrouillage du cadenas (data->cadenas) est actif.
//Pour éviter le "problème du philosophe pair" 
//(où tous les philosophes pairs prennent d'abord leur fourchette droite
// et bloquent le système),
// ajoute un délai de 500 ms 
//pour les philosophes pairs avant de commencer leur cycle.
void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = &philo->data;
	if (data->nbr_philo == 1)
	{
		one_philo(data);
		return (EXIT_SUCCESS);
	}
	if (philo->id % 2)
		usleep(500);
	while (check_cadenas(data))
	{
		if (check_cadenas(data) != 0)
			philo_eats(data, philo);
		if (check_cadenas(data) != 0)
			philo_sleeps(data, philo);
	}
	return (0);
}

// FCT FORKS / EAT / SLEEP / THINK
// Chacune met à jour l'état du philosophe (impression du message associé)
// en fonction de l'action qu'il effectue
// (prendre une fourchette, manger, dormir, penser).
// Respecte la condition check_cadenas(data) avant de procéder,
// ce qui assure qu'elles n'exécutent ces actions 
// que si le cadenas est verrouillé.
void	philo_forks(t_data *data, t_philo *philo)
{
	if (check_cadenas(data))
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&data->message);
		if (check_cadenas(data))
		{
			printf("%llu %d has taken a fork\n", time_passed(data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_lock(&philo->left_fork);
		if (check_cadenas(data))
		{
			printf("%llu %d has taken a fork\n", time_passed(data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&data->message);
	}
}

void	philo_eats(t_data *data, t_philo *philo)
{
	if (check_cadenas(data))
	{
		philo_forks(data, philo);
		pthread_mutex_lock(&data->message);
		if (check_cadenas(data))
		{
			printf("%llu %d is eating\n", time_passed(data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&data->message);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->mutex_philo);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->mutex_philo);
		pthread_mutex_lock(&philo->mutex_meal);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->mutex_meal);
	}
}

void	philo_sleeps(t_data *data, t_philo *philo)
{
	if (check_cadenas(data))
	{
		pthread_mutex_lock(&data->message);
		if (check_cadenas(data))
		{
			printf("%llu %d is sleeping\n", time_passed(data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&data->message);
		ft_usleep(data->time_to_sleep);
		philo_thinks(data, philo);
	}
}

void	philo_thinks(t_data *data, t_philo *philo)
{
	if (check_cadenas(data))
	{
		pthread_mutex_lock(&data->message);
		if (check_cadenas(data))
		{
			printf("%llu %d is thinking\n", time_passed(data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&data->message);
	}
}
