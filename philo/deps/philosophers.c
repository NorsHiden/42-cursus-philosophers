/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/03/24 17:32:30 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	throw_error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

void	setup_philos(int c, char **v, philo_t *philo)
{
	int	i;

	philo->n_philos = ft_atoi(v[1]);
	philo->time_to_die = ft_atoi(v[2]);
	philo->time_to_eat = ft_atoi(v[3]);
	philo->time_to_sleep = ft_atoi(v[4]);
	philo->actual_philo  = 0;
	if (c == 6)
		philo->notepme = ft_atoi(v[5]);
	if (!philo->n_philos || !philo->time_to_die
		|| !philo->time_to_eat || !philo->time_to_sleep)
			throw_error("Invalid arguments.\n");
	philo->chopsticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->n_philos);
	if (!philo->chopsticks)
		throw_error("Not enough memory is available.\n");
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->n_philos);
	if (!philo->threads)
		throw_error("Not enough memory is available.\n");
	i = 0;
	while (i < philo->n_philos)
		pthread_mutex_init(&philo->chopsticks[i++], NULL);
}

long right_now(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_freeze(long	freeze_time)
{
	long time;

	time = right_now();
	while (right_now() - time < freeze_time)
		usleep(100);
}


void	*philo_routine(void *param)
{
	philo_t	*philo;
	int		philo_id;

	philo = param;
	pthread_mutex_lock(&philo->philo_mutex);
	philo_id = philo->actual_philo++;
	pthread_mutex_unlock(&philo->philo_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->chopsticks[philo_id]);
		printf("%ld ms %d has taken a fork.\n", (right_now() - philo->init_time), philo_id + 1);
		pthread_mutex_lock(&philo->chopsticks[(philo_id + 1) % philo->n_philos]);
		printf("%ld ms %d has taken a fork.\n", (right_now() - philo->init_time), philo_id + 1);
		printf("%ld ms %d is eating.\n", (right_now() - philo->init_time), philo_id + 1);
		ft_freeze(philo->time_to_eat);
		pthread_mutex_unlock(&philo->chopsticks[philo_id]);
		pthread_mutex_unlock(&philo->chopsticks[(philo_id + 1) % philo->n_philos]);
		printf("%ld ms %d is sleeping.\n", (right_now() - philo->init_time), philo_id + 1);
		ft_freeze(philo->time_to_sleep);
		printf("%ld ms %d is thinking.\n", (right_now() - philo->init_time), philo_id + 1);
	}
	return (0);
}

int	main(int c, char **v)
{
	philo_t	philo;
	int		i;

	if (c != 5 && c != 6)
		throw_error("Invalid arguments.\n");
	setup_philos(c, v, &philo);
	i = 0;
	philo.init_time = right_now();
	while (i < philo.n_philos)
	{
		pthread_create(&philo.threads[i++], NULL, philo_routine, &philo);
		usleep(100);
	}
	i = 0;
	while (i < philo.n_philos)
		pthread_join(philo.threads[i++], NULL);
	return (0);
}