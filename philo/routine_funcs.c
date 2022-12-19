/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:57 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 10:10:35 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_phi *philo)
{
	while (!*philo->end)
	{
			pthread_mutex_lock(philo->r_fork.fork);
			pthread_mutex_lock(philo->l_fork.fork);
			mutex_print(philo, "has taken a fork");
			mutex_print(philo, "has taken a fork");
			break ;
	}
}

void	ft_eat(t_phi *philo)
{
	pthread_mutex_lock(philo->m_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->m_last_eat);
	mutex_print(philo, "is eating");

	pthread_mutex_lock(philo->m_num_eat);
	philo->n_eats++;
	pthread_mutex_unlock(philo->m_num_eat);
	if (s_sleep(philo, philo->logic->t_eat))
		return ;
}

void	ft_sleep(t_phi *philo)
{
	mutex_print(philo, "is sleeping");
	if (s_sleep(philo, philo->logic->t_slp))
		return ;
}

void	ft_think(t_phi *philo)
{
	mutex_print(philo, "is thinking");
}

void	ft_leave_forks(t_phi *philo)
{
	pthread_mutex_unlock(philo->r_fork.fork);
	pthread_mutex_unlock(philo->l_fork.fork);
}
