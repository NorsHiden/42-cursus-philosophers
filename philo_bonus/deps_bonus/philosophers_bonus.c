/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/05/10 15:21:10 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	philo_death_bonus(t_philo *philo)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (waitpid(0, &exit_code, 0) != -1)
	{
		if (exit_code)
			terminate_sim(philo, philo->n_philos - 1);
	}
	return (0);
}

void	terminate_sim(t_philo *philo, int max)
{
	int	i;

	i = 0;
	while (i <= max)
		kill(philo->process[i++], SIGKILL);
	exit(0);
}

static void	start_routine(t_philo *philo, int philo_id)
{
	while (philo_id < philo->n_philos)
	{
		philo->cons_time = philo->init_time;
		philo->process[philo_id] = fork();
		if (philo->process[philo_id] < 0)
			terminate_sim(philo, philo_id);
		if (!philo->process[philo_id])
			process_main(philo, philo_id);
		usleep(30);
		philo_id += 2;
	}
}

int	main(int c, char **v)
{
	t_philo	*philo;

	if (c < 5 || c > 6)
		return (throw_error_bonus("Invalid arguments.\n"));
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (throw_error_bonus("Not enough memory is available.\n"));
	if (check_args_bonus(c, v) || setup_philos_bonus(c, v, philo))
		return (1);
	philo->init_time = right_now();
	start_routine(philo, 0);
	start_routine(philo, 1);
	return (philo_death_bonus(philo));
}
