/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:07:38 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/24 15:56:39 by vipereir         ###   ########.fr       */
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
	int				number_phi;
	long			t_die;
	long			t_eat;
	long			t_slp;
	int				number_eat;
}				t_logic;

typedef struct	s_table{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_table;

typedef struct	s_phi{

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*philo;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	int						id;
	int						n_eats;
	long					last_eat;
	typedef struct s_logic	*logic;
	typedef struct s_phi	*next;
}				t_phi_list;

long	get_time(void);
int		ft_atoi(const char *str);
int	ft_malloc_zero(t_logic *logic, t_phi **phis);
int	ft_error(char *s);


#endif
