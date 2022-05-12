/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 07:59:28 by nelidris          #+#    #+#             */
/*   Updated: 2022/05/10 09:35:45 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static int	setup_alloc_bonus(t_philo *philo)
{
	philo->process = (pid_t *)malloc(sizeof(pid_t) * philo->n_philos);
	if (!philo->process)
		return (throw_error_bonus("Not enough memory is available.\n"));
	return (0);
}

static void	init_vars_bonus(char **v, int c, t_philo *philo)
{
	philo->n_philos = ft_atoi(v[1]);
	philo->time_to_die = ft_atoi(v[2]);
	philo->time_to_eat = ft_atoi(v[3]);
	philo->time_to_sleep = ft_atoi(v[4]);
	philo->actual_philo = 0;
	philo->has_finished = 0;
	philo->cons_time = 0;
	if (c == 6)
	{
		philo->notepme = ft_atoi(v[5]);
		if (philo->notepme <= 0)
			philo->notepme = -2;
	}
	else
		philo->notepme = -1;
}

int	setup_philos_bonus(int c, char **v, t_philo *philo)
{
	init_vars_bonus(v, c, philo);
	if (philo->n_philos <= 0 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0
		|| philo->notepme < -1)
		return (throw_error_bonus("Invalid arguments.\n"));
	if (setup_alloc_bonus(philo))
		return (1);
	sem_unlink("philo_sem");
	sem_unlink("message");
	sem_unlink("chopsticks");
	philo->philo_sem = sem_open("philo_sem", O_CREAT, 0644, 1);
	philo->message = sem_open("message", O_CREAT, 0644, 1);
	philo->chopsticks = sem_open("chopsticks", O_CREAT, 0644, philo->n_philos);
	return (0);
}

int	check_args_bonus(int c, char **v)
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
		{
			throw_error_bonus("Invalid arguments.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
