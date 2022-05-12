/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/05/10 15:16:08 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	all_finished(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philos)
	{
		if (philo->notepme == -1 || philo->notepme_meals[i] < philo->notepme)
			return (0);
		i++;
	}
	philo->all_meals = 0;
	return (1);
}

static int	philo_death(t_philo *philo)
{
	int		i;

	i = 0;
	while (!all_finished(philo))
	{
		if (right_now() - philo->cons_time[i] >= philo->time_to_die)
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
	pthread_mutex_lock(&philo->message);
	return (0);
}

static void	start_routine(t_philo *philo,
		void*(philo_routine)(void*), int philo_id)
{
	while (philo_id < philo->n_philos)
	{
		philo->cons_time[philo_id] = philo->init_time;
		philo->notepme_meals[philo_id] = 0;
		philo->actual_philo = philo_id;
		pthread_create(&philo->threads[philo_id], NULL, philo_routine, philo);
		usleep(50);
		philo_id += 2;
	}
}

int	main(int c, char **v)
{
	t_philo	*philo;

	if (c != 5 && c != 6)
		return (throw_error("Invalid arguments.\n"));
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (throw_error("Not enough memory is available.\n"));
	if (check_args(c, v) || setup_philos(c, v, philo))
		return (1);
	philo->init_time = right_now();
	start_routine(philo, philo_routine, 0);
	start_routine(philo, philo_routine, 1);
	return (philo_death(philo));
}
