/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ethics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:03:34 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 10:39:25 by vipereir         ###   ########.fr       */
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

typedef struct s_dining_room {
	pthread_mutex_t	*forks;
	pthread_t		*philos;
}t_dining_room;

/* utils-funcs */

int	ft_atoi(const char *str);

#endif
