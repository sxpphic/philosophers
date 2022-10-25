/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:03:34 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 10:30:00 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ETHICS_H
# define ETHICS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_conf {
	int	number_of_philosophers;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int	number_of_time_each_philosopher_must_eat;
}t_conf;

typedef struct s_philo {
	pthread_mutex_t	*left_fork;
	pthread_t		*philo;
	pthread_mutex_t	*right_fork;
}t_philo;

/* utils-funcs */

int	ft_atoi(const char *str);

#endif
