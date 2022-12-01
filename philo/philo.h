/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:07:38 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/30 11:26:10 by vipereir         ###   ########.fr       */
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
	int				print_var;
}				t_table;

typedef struct	s_phi{

	pthread_mutex_t	*l_fork;
	pthread_t		*philo;
	struct s_phi	*l_philo;
	pthread_mutex_t	*r_fork;
	int				f;
	int				*print_var;
	pthread_mutex_t	*print;
	int				id;
	int				n_eats;
	long			last_eat;
	long			start_time;
	struct s_logic	*logic;
	int				end;
}				t_phi;

long	get_time(void);
int		ft_atoi(const char *str);
int	ft_malloc_zero(t_table *table, t_logic *logic, t_phi **phis);
int	ft_error(char *s);



int	ft_check_imputs(char **argv);
void	ft_cleaning(t_table *table, t_phi **phis);
void	set_imput(int argc, char *argv[], t_logic *logic);
int	ft_init_forks(t_table *table, t_logic *logic);
int	ft_philo_create(t_table *table,t_logic *logic, t_phi **philos);
int	ft_wait_philo(t_table *table, t_logic *logic);
int	ft_destroy_forks(t_table *table, t_logic *logic);
void	*ft_philosopher(void	*arg);
void	mutex_print(t_phi *philo, char *s);


#endif
