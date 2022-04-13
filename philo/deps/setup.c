/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 07:59:28 by nelidris          #+#    #+#             */
/*   Updated: 2022/04/13 16:19:57 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	setup_alloc(t_philo *philo)
{
	philo->cons_time = (long *)malloc(sizeof(long) * philo->n_philos);
	if (!philo->cons_time)
		return (1);
	philo->has_finished = (char *)malloc(sizeof(char) * philo->n_philos);
	if (!philo->has_finished)
		return (1);
	philo->chopsticks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * philo->n_philos);
	if (!philo->chopsticks)
		return (1);
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->n_philos);
	if (!philo->threads)
		return (1);
	return (0);
}

static void	init_vars(char **v, int c, t_philo *philo)
{
	philo->n_philos = ft_atoi(v[1]);
	philo->time_to_die = ft_atoi(v[2]);
	philo->time_to_eat = ft_atoi(v[3]);
	philo->time_to_sleep = ft_atoi(v[4]);
	philo->actual_philo = 0;
	if (c == 6)
	{
		philo->notepme = ft_atoi(v[5]);
		if (philo->notepme <= 0)
			philo->notepme = -2;
	}
	else
		philo->notepme = -1;
}

int	setup_philos(int c, char **v, t_philo *philo)
{
	int	i;

	init_vars(v, c, philo);
	if (philo->n_philos <= 0 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0
		|| philo->notepme < -1)
		return (throw_error("Invalid arguments.\n"));
	if (setup_alloc(philo))
		return (throw_error("Not enough memory is available.\n"));
	i = 0;
	pthread_mutex_init(&philo->philo_mutex, NULL);
	pthread_mutex_init(&philo->message, NULL);
	while (i < philo->n_philos)
		pthread_mutex_init(&philo->chopsticks[i++], NULL);
	return (0);
}

int	check_args(int c, char **v)
{
	int	i;
	int	j;

	i = 1;
	while (i < c)
	{
		j = 0;
		if (v[i][0] == '-' || v[i][0] == '+')
			j++;
		while (v[i][j] >= '0' && v[i][j] <= '9')
			j++;
		if (v[i][j])
			return (throw_error("Invalid arguments.\n"));
		i++;
	}
	return (0);
}
