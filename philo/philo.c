/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 09:49:24 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	s_sleep(t_phi *philo, unsigned long time)
{
	long	t;

	t = get_time() + time / 1;
	while (get_time() < t)
	{
		pthread_mutex_lock(philo->m_end);
		if (*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			return (1);
		}
		else
			pthread_mutex_unlock(philo->m_end);
		usleep(1000);
	}
	return (0);
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
		pthread_mutex_lock(philo->m_end);
		if (!*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			take_forks(philo);
		}
		else
			pthread_mutex_unlock(philo->m_end);
		pthread_mutex_lock(philo->m_end);
		if (!*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			ft_eat(philo);
		}
		else
			pthread_mutex_unlock(philo->m_end);
		ft_leave_forks(philo);
		pthread_mutex_lock(philo->m_end);
		if (!*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			ft_sleep(philo);
		}
		else
			pthread_mutex_unlock(philo->m_end);
		pthread_mutex_lock(philo->m_end);
		if (!*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			ft_think(philo);
		}
		else
			pthread_mutex_unlock(philo->m_end);
	}
	return (NULL);
}

int	ft_check_int(char	**argv)
{
	int		i;
	long	nb;

	i = 1;
	while (argv[i])
	{
		nb = ft_atoi(argv[i]);
		if ((nb > 2147483647) || (nb < -2147483648))
			return (-1);
		else
			i++;
	}
	return (0);
}

int	check_inputs(int argc, char *argv[], t_logic *logic)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_check_int(argv) != 0)
			return (!ft_error("imput error"));
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
