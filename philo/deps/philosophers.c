/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/04/13 16:14:31 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	all_finished(t_philo *philo)
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

int	philo_death(t_philo *philo)
{
	int		i;

	i = 0;
	while (!all_finished(philo))
	{
		if (right_now() - philo->cons_time[i] >= philo->time_to_die
			&& !philo->has_finished[i])
		{
			pthread_mutex_lock(&philo->message);
			printf("%ld ms %d died.\n", right_now() - philo->init_time, i + 1);
			return (1);
		}
		if (i + 1 == philo->n_philos)
			i = 0;
		else
			i++;
	}
	return (0);
}

int	main(int c, char **v)
{
	t_philo	*philo;
	int		i;

	if (c != 5 && c != 6)
		return (throw_error("Invalid arguments.\n"));
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (throw_error("Not enough memory is available.\n"));
	if (check_args(c, v) || setup_philos(c, v, philo))
		return (1);
	philo->init_time = right_now();
	i = 0;
	while (i < philo->n_philos)
	{
		philo->cons_time[i] = philo->init_time;
		philo->has_finished[i] = 0;
		pthread_create(&philo->threads[i], NULL, philo_routine, philo);
		usleep(100);
		i++;
	}
	return (philo_death(philo));
}
