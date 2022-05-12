/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:02:43 by nelidris          #+#    #+#             */
/*   Updated: 2022/05/10 15:55:45 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void	display_message(char *message, int philo_id, t_philo *philo)
{
	sem_wait(philo->message);
	printf(message, (right_now() - philo->init_time), philo_id + 1);
	sem_post(philo->message);
}

static void	take_a_fork(t_philo *philo, int i, int philo_id)
{
	sem_wait(philo->chopsticks);
	display_message("%ld ms %d has taken a fork.\n", philo_id, philo);
	sem_wait(philo->chopsticks);
	display_message("%ld ms %d has taken a fork.\n", philo_id, philo);
	philo->cons_time = right_now();
	display_message("%ld ms %d is eating.\n", philo_id, philo);
	if (philo->notepme != -1 && i >= philo->notepme)
	{
		sem_wait(philo->message);
		exit(1);
	}
	ft_freeze(philo->time_to_eat);
	sem_post(philo->chopsticks);
	sem_post(philo->chopsticks);
}

void	*philo_routine_bonus(void *param)
{
	int		i;
	t_philo	*philo;

	philo = param;
	i = 0;
	while (1)
	{
		take_a_fork(philo, i++, philo->actual_philo);
		display_message("%ld ms %d is sleeping.\n", philo->actual_philo, philo);
		ft_freeze(philo->time_to_sleep);
		display_message("%ld ms %d is thinking.\n", philo->actual_philo, philo);
	}
	philo->has_finished = 1;
	exit(0);
}

void	process_main(t_philo *philo, int i)
{
	pthread_t	thread;

	sem_wait(philo->philo_sem);
	philo->actual_philo = i;
	sem_post(philo->philo_sem);
	pthread_create(&thread, NULL, philo_routine_bonus, philo);
	while (!philo->has_finished)
	{
		if (right_now() - philo->cons_time >= philo->time_to_die
			&& !philo->has_finished)
		{
			sem_wait(philo->message);
			printf("%ld ms %d died.\n", right_now() - philo->init_time, i + 1);
			exit(1);
		}
	}	
}
