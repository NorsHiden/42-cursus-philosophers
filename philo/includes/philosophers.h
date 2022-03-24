/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:48 by nelidris          #+#    #+#             */
/*   Updated: 2022/03/24 17:13:13 by nelidris         ###   ########.fr       */
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

typedef struct philo_s {
    int             notepme;
    int             n_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             actual_philo;
    long            init_time;
    pthread_t       *threads;
    pthread_mutex_t philo_mutex;
    pthread_mutex_t *chopsticks;
}   philo_t;


size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);

#endif