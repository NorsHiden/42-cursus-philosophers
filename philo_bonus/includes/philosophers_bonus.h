/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:48 by nelidris          #+#    #+#             */
/*   Updated: 2022/04/05 16:40:09 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct t_philo {
	int				notepme;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				actual_philo;
	char			has_finished;
	long			cons_time;
	long			init_time;
	pid_t			*process;
	sem_t			*message;
	sem_t			*philo_sem;
	sem_t			*chopsticks;
}	t_philo;

/*___________UTILS___________*/
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
/*___________ROUTINE___________*/
void	*philo_routine_bonus(void *param);
void	process_main(t_philo *philo, int i);
void	terminate_sim(t_philo *philo, int max);
/*___________SETUP___________*/
int		setup_philos_bonus(int c, char **v, t_philo *philo);
int		check_args_bonus(int c, char **v);
/*___________TIME___________*/
long	right_now(void);
void	ft_freeze(long freeze_time);
/*___________ERRORS___________*/
int		throw_error_bonus(char *error);
#endif