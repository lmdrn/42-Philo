/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:11:15 by lmedrano          #+#    #+#             */
/*   Updated: 2023/08/17 15:56:31 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//FCT ONE_PHILO
// Gère le cas où il n'y a qu'un seul philosophe.
// Imprime le message de prise de fourchette 
// et attend le temps défini par data->time_to_die.
int	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	return (0);
}

//FCT ASSIGN_THREADS
//La boucle crée un thread pour chaque philosophe
// en appelant la fonction pthread_create.
int	assign_threads(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			printf("Error creating philo_thread %d\n", philo[i].id);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

// FCT CHECK_CADENAS
// Verrouille et déverrouille le cadenas
// pour vérifier s'il est actif ou non.
// Retourne EXIT_FAILURE si le cadenas est actif (simulation en cours)
// et EXIT_SUCCESS si le cadenas est désactivé (simulation terminée).
int	check_cadenas(t_data *data)
{
	pthread_mutex_lock(&data->cadenas_mutex);
	if (data->cadenas == 1)
	{
		pthread_mutex_unlock(&data->cadenas_mutex);
		return (EXIT_FAILURE);
	}
	else
	{
		pthread_mutex_unlock(&data->cadenas_mutex);
		return (EXIT_SUCCESS);
	}
}
