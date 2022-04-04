/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:48 by nelidris          #+#    #+#             */
/*   Updated: 2022/04/04 20:49:45 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
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
	char			*has_finished;
	long			*cons_time;
	long			init_time;
	pthread_t		*threads;
	pthread_mutex_t	death;
	pthread_mutex_t	message;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*chopsticks;
}	t_philo;

/*___________UTILS___________*/
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
/*___________ROUTINE___________*/
void	*philo_routine(void *param);
/*___________SETUP___________*/
int		setup_philos(int c, char **v, t_philo *philo);
int		check_args(int c, char **v);
/*___________TIME___________*/
long	right_now(void);
void	ft_freeze(long freeze_time);
/*___________ERRORS___________*/
int		throw_error(char *error);
#endif