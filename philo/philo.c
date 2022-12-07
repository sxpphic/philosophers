/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/05 10:23:08 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	s_sleep(t_phi *philo, unsigned long time)
{
	long	t;

	t = get_time() + time / 1;
	while (get_time() < t)
	{
		if (*philo->end)
			return (1);
		usleep(1000);
	}
	return (0);
}

void	take_forks(t_phi *philo)
{
	while (!*philo->end)
	{
		if (philo->r_fork.state == 0 && philo->l_fork.state == 0)
		{
			pthread_mutex_lock(philo->r_fork.fork);
			pthread_mutex_lock(philo->l_fork.fork);
			philo->r_fork.state = 1;
			philo->l_fork.state = 1;
			mutex_print(philo, "has taken a fork");
			mutex_print(philo, "has taken a fork");
			break ;
		}
	}
}

int	ft_eat(t_phi *philo)
{
	philo->last_eat = get_time();
	mutex_print(philo, "is eating");
	philo->n_eats++;
	if (s_sleep(philo, philo->logic->t_eat))
		return (1);
	return (0);
}

int	ft_sleep(t_phi *philo)
{
	mutex_print(philo, "is sleeping");
	if (s_sleep(philo, philo->logic->t_slp))
		return (1);
	return (0);
}

void	ft_think(t_phi *philo)
{
	mutex_print(philo, "is thinking");
}

void	ft_leave_forks(t_phi *philo)
{
	philo->r_fork.state = 0;
	philo->l_fork.state = 0;
	pthread_mutex_unlock(philo->r_fork.fork);
	pthread_mutex_unlock(philo->l_fork.fork);
}

void	*ft_philosopher(void	*arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	if (philo->logic->number_phi == 1)
	{
		while (!*philo->end)
			s_sleep(philo, 100);
	}
	while (!*philo->end)
	{
		if (!*philo->end)
			take_forks(philo);
		if (!*philo->end)
			ft_eat(philo);
		ft_leave_forks(philo);
		if (!*philo->end)
			ft_sleep(philo);
		if (!*philo->end)
			ft_think(philo);
	}
	return (NULL);
}

int	ft_everybody_eats(t_phi *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].logic->number_phi)
	{
		if (philos[i].n_eats >= philos[i].logic->number_eat)
			i++;
		else
			return (0);
		if (i == philos[0].logic->number_phi)
			break ;
	}
	return (1);
}

int	check_end(t_phi *philos, int i)
{
	long	time;

	time = get_time();
	if (time - philos[i].last_eat > philos[0].logic->t_die)
	{
		*philos[i].end = 1;
		usleep(100);
		printf("%ld %i %s\n", time / 1000, philos[i].id + 1, "died");
		return (1);
	}
	if (philos[i].logic->number_eat && ft_everybody_eats(philos))
	{
		*philos[i].end = 1;
		usleep(100);
		return (1);
	}
	return (0);
}

void	*ft_seeker(void *arg)
{
	t_phi	*philos;
	int		i;

	philos = (t_phi *)arg;
	i = 0;
	while (i < philos[0].logic->number_phi)
	{
		if (check_end(philos, i))
			break ;
		i++;
		if (i == philos[0].logic->number_phi)
			i = 0;
	}
	return (NULL);
}

int	ft_seeker_create(t_phi	*philos)
{
	pthread_t		seeker;

	if (pthread_create(&seeker, NULL, ft_seeker, (void *)philos))
		return (-1);
	pthread_join(seeker, NULL);
	return (0);
}

int	check_inputs(int argc, char *argv[], t_logic *logic)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_check_imputs(argv) != 0)
			return (!ft_error("imput error"));
		memset(logic, 0x0, sizeof(t_logic));
		set_imput(argc, argv, logic);
	}
	else
		return (!ft_error("wrong imput"));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	t_phi			*philos;
	t_logic			logic;

	if (check_inputs(argc, argv, &logic))
		return (0);
	if (ft_malloc_zero(&table, &logic, &philos) != 0)
		return (ft_error("malloc error"));
	if (ft_init_forks(&table, &logic) != 0)
		return (ft_error("forks error"));
	if (ft_philo_create(&table, &logic, &philos) != 0)
		return (ft_error("thread error (philo)"));
	if (ft_seeker_create(philos))
		return (ft_error("thread error (seeker)"));
	if (ft_wait_philo(&table, &logic) != 0)
		return (ft_error("join error"));
	if (ft_destroy_forks(&table, &logic) != 0)
		return (ft_error("forks_d error"));
	ft_cleaning(&table, &philos);
	return (0);
}
