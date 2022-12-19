/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 10:30:28 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_and_action(t_phi *philo, void (*f)(t_phi *philo))
{
	pthread_mutex_unlock(philo->m_end);
	(*f)(philo);
}

void	take_and_eat(t_phi *philo)
{
	pthread_mutex_lock(philo->m_end);
	if (!*philo->end)
		unlock_and_action(philo, take_forks);
	else
		pthread_mutex_unlock(philo->m_end);
	pthread_mutex_lock(philo->m_end);
	if (!*philo->end)
		unlock_and_action(philo, ft_eat);
	else
		pthread_mutex_unlock(philo->m_end);
}

void	sleep_and_think(t_phi *philo)
{
	pthread_mutex_lock(philo->m_end);
	if (!*philo->end)
		unlock_and_action(philo, ft_sleep);
	else
		pthread_mutex_unlock(philo->m_end);
	pthread_mutex_lock(philo->m_end);
	if (!*philo->end)
		unlock_and_action(philo, ft_think);
	else
		pthread_mutex_unlock(philo->m_end);
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
		take_and_eat(philo);
		ft_leave_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
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
