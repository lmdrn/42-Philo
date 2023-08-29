/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:06:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/29 18:20:48 by lmedrano         ###   ########.fr       */
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

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (check_cadenas(philo))
	{
		philo_forks(philo);
		if (check_cadenas(philo) == 0)
			break ;
		philo_eats(philo);
		if (check_cadenas(philo) == 0)
			break ;
		philo_sleeps(philo);
		if (check_cadenas(philo) == 0)
			break ;
		philo_thinks(philo);
		if (check_cadenas(philo) == 0)
			break ;
	}
	return (NULL);
}

// FCT FORKS / EAT / SLEEP / THINK
// Chacune met à jour l'état du philosophe (impression du message associé)
// en fonction de l'action qu'il effectue
// (prendre une fourchette, manger, dormir, penser).
// Respecte la condition check_cadenas(data) avant de procéder,
// ce qui assure qu'elles n'exécutent ces actions 
// que si le cadenas est verrouillé.
void	philo_forks(t_philo *philo)
{
	if (check_cadenas(philo))
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->data->message);
		if (check_cadenas(philo))
		{
			printf("%llu %d has taken a fork\n",
				time_passed(philo->data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_lock(philo->left_fork);
		if (check_cadenas(philo))
		{
			printf("%llu %d has taken a fork\n",
				time_passed(philo->data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&philo->data->message);
	}
}

void	philo_eats(t_philo *philo)
{
	if (check_cadenas(philo))
	{
		pthread_mutex_lock(&philo->data->message);
		if (check_cadenas(philo))
		{
			printf("%llu %d is eating\n", time_passed(philo->data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&philo->data->message);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->mutex_lastmeal);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->mutex_lastmeal);
		pthread_mutex_lock(&philo->mutex_meal);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->mutex_meal);
	}
}

void	philo_sleeps(t_philo *philo)
{
	if (check_cadenas(philo))
	{
		pthread_mutex_lock(&philo->data->message);
		if (check_cadenas(philo))
		{
			printf("%llu %d is sleeping\n", time_passed(philo->data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&philo->data->message);
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	philo_thinks(t_philo *philo)
{
	if (check_cadenas(philo))
	{
		pthread_mutex_lock(&philo->data->message);
		if (check_cadenas(philo))
		{
			printf("%llu %d is thinking\n", time_passed(philo->data->start_time,
					get_current_time()), philo->id);
		}
		pthread_mutex_unlock(&philo->data->message);
	}
}
