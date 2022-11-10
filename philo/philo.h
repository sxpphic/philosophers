/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:07:38 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/10 11:48:16 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct	s_logic{
	/* game rules */

	int				number_phi;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				number_eat;

	/* philosophers and forks arrays*/

	pthread_t		*philos;
	pthread_mutex_t	*forks;

}				t_logic;

int	ft_atoi(const char *str);


#endif
