/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:02:43 by nelidris          #+#    #+#             */
/*   Updated: 2022/03/28 15:43:58 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	display_message(char *message, int philo_id, philo_t *philo)
{
	pthread_mutex_lock(&philo->message);
	printf(message, (right_now() - philo->init_time), philo_id + 1);
	pthread_mutex_unlock(&philo->message);
}

void	*philo_routine(void *param)
{
	philo_t	*philo;
	int		philo_id;
	int		i;

	philo = param;
	pthread_mutex_lock(&philo->philo_mutex);
	philo_id = philo->actual_philo++;
	pthread_mutex_unlock(&philo->philo_mutex);
	i = 0;
	while (philo->notepme == -1 || i++ < philo->notepme)
	{
		pthread_mutex_lock(&philo->chopsticks[philo_id]);
		display_message("%ld ms %d has taken a fork.\n", philo_id, philo);
		pthread_mutex_lock(&philo->chopsticks[(philo_id + 1) % philo->n_philos]);
		display_message("%ld ms %d has taken a fork.\n", philo_id, philo);
		pthread_mutex_lock(&philo->death);
		philo->cons_time[philo_id] = right_now();
		pthread_mutex_unlock(&philo->death);
		display_message("%ld ms %d is eating.\n", philo_id, philo);
		ft_freeze(philo->time_to_eat);
		//philo->is_eating[philo_id] = 0;
		pthread_mutex_unlock(&philo->chopsticks[philo_id]);
		pthread_mutex_unlock(&philo->chopsticks[(philo_id + 1) % philo->n_philos]);
		display_message("%ld ms %d is sleeping.\n", philo_id, philo);
		ft_freeze(philo->time_to_sleep);
		display_message("%ld ms %d is thinking.\n", philo_id, philo);
	}
	philo->has_finished[philo_id] = 1;
	return (0);
}
