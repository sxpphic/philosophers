/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/28 16:27:18 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void s_sleep(t_phi *philo, unsigned long time)
{
	
}
*/

void	take_forks(t_phi *philo)
{
//	if (philo->f && philo->l_philo->f)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		philo->f = 0;
		philo->l_philo->f = 0;
		mutex_print(philo, "has taken a fork");
		mutex_print(philo, "has taken a fork");
	}
}

void	ft_eat(t_phi *philo)
{
	mutex_print(philo, "is eating");
	philo->f = 1;
	philo->l_philo->f = 1;
	philo->last_eat = get_time();
	philo->n_eats++;
	usleep(philo->logic->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	//sleep
}

void	ft_sleep(t_phi *philo)
{
	mutex_print(philo, "is sleeping");
	usleep(philo->logic->t_slp);
	//sleep
}

void	ft_think(t_phi *philo)
{
	mutex_print(philo, "is thinking");
}

void	*ft_philosopher(void	*arg)
{
	t_phi	*philo;

	philo = (t_phi*)arg;
	while (1)
	{
//		while (philo->f || philo->l_philo->f)
			take_forks(philo);
//		if (philo->f == 0 && philo->l_philo->f == 0)
//		{
			ft_eat(philo);
			ft_sleep(philo);
			ft_think(philo);
//		}
	}
	return (NULL);
}


int	ft_everybody_eats(t_phi *philos)
{
	int	i;

	i = 0;
	while (i < philos[i].logic->number_phi)
	{
		if (philos[i].n_eats >= philos[i].logic->number_eat)
			i++;
		else
			return (0);
		if (i == philos[0].logic->number_phi)
			break;
	}
	return (1);
}

void	*ft_seeker(void *arg)
{
	t_phi	*philos;
	int		n_phi;
	int		i;
	int		n_eats;
	long	t_die;


	philos = (t_phi *)arg;
	n_phi = philos[0].logic->number_phi;
	t_die = philos[0].logic->t_die / 1000;
	(void)n_eats;
	i = 0;
	while (i < n_phi)
	{
		if (get_time() - philos[i].last_eat > t_die)
		{
			pthread_mutex_lock(philos[i].print);
			printf("%ld %i %s\n", get_time(), philos[i].id + 1, "died");
			exit(0); //  função de acabar o jogo
		}
		if (philos[i].logic->number_eat && ft_everybody_eats(philos))
		{
			pthread_mutex_lock(philos[i].print);
			exit(0); //  função de acabar o jogo
		}
//		printf("philo %i, time: %ld\n", i, get_time());
		i++;
		if (i == n_phi)
			i = 0;
	}
	return (NULL);
}


int	main(int argc, char *argv[])
{
	t_table			table;
	t_phi			*philos;
	t_logic			logic;
	pthread_t		seeker;


	if (ft_check_imputs(argv) != 0)
		return (ft_error("imput error"));
	memset(&logic, 0x0, sizeof(t_logic));
	if (argc == 5 || argc == 6)
		set_imput(argc, argv, &logic);
	else
		return (ft_error("wrong imput"));
	if (ft_malloc_zero(&table, &logic, &philos) != 0)
		return (ft_error("malloc error"));
	if (ft_init_forks(&table, &logic) != 0)
		return (ft_error("forks error"));
	if (ft_philo_create(&table, &logic, &philos) != 0)
		return (ft_error("thread error"));
	pthread_create(&seeker, NULL, ft_seeker, (void *)philos);
	if (ft_wait_philo(&table, &logic) != 0)
		return (ft_error("join error"));
	if (ft_destroy_forks(&table, &logic) != 0)
		return (ft_error("forks_d error"));
	ft_cleaning(&table, &philos);
	return (0);
}

//makefile relink
