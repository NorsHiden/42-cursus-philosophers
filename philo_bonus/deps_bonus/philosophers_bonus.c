/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/04/05 21:40:47 by nelidris         ###   ########.fr       */
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

int	main(int c, char **v)
{
	int		i;
	t_philo	*philo;

	if (c != 5 && c != 6)
		throw_error_bonus("Invalid arguments.\n");
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (throw_error_bonus("Not enough memory is available.\n"));
	if (check_args_bonus(c, v) || setup_philos_bonus(c, v, philo))
		return (1);
	i = 0;
	philo->init_time = right_now();
	while (i < philo->n_philos)
	{
		philo->cons_time = philo->init_time;
		philo->process[i] = fork();
		if (philo->process[i] < 0)
			terminate_sim(philo, i);
		if (!philo->process[i])
			process_main(philo, i);
		usleep(100);
		i++;
	}
	return (philo_death_bonus(philo));
}
