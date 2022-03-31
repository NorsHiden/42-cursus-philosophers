/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/03/29 18:14:35 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	all_finished(philo_t *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philos)
	{
		if (!philo->has_finished[i])
			return (0);
		i++;
	}
	return (1);
}

int	philo_death(philo_t *philo)
{
	int		i;

	i = 0;
	while (!all_finished(philo))
	{
		pthread_mutex_lock(&philo->death);
		if (right_now() - philo->cons_time[i] >= philo->time_to_die && !philo->has_finished[i])
		{
			pthread_mutex_lock(&philo->message);
			printf("%ld ms %d died.\n", right_now() - philo->init_time, i + 1);
			return (1);
		}
		pthread_mutex_unlock(&philo->death);
		if (i + 1 == philo->n_philos)
			i = 0;
		else
			i++;
	}
	return (0);
}

int	main(int c, char **v)
{
	philo_t	*philo;
	int		i;

	if (c != 5 && c != 6)
		throw_error("Invalid arguments.\n");
	philo = (philo_t *)malloc(sizeof(philo_t));
	if (!philo)
	{
		throw_error("Not enough memory is available.\n");
		return (1);
	}
	if (check_args(c, v) || setup_philos(c, v, philo))
		return (1);
	i = 0;
	philo->init_time = right_now();
	while (i < philo->n_philos)
	{
		philo->cons_time[i] = philo->init_time;
		philo->has_finished[i] = 0;
		pthread_create(&philo->threads[i], NULL, philo_routine, philo);
		pthread_detach(philo->threads[i++]);
		usleep(100);
	}
	return (philo_death(philo));
}
