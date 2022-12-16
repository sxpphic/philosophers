/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:57 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/14 11:27:48 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_phi *philo)
{
	while (!*philo->end)
	{
//		if (philo->r_fork.state == 0 && philo->l_fork.state == 0)
		{
			pthread_mutex_lock(philo->r_fork.fork);
			pthread_mutex_lock(philo->l_fork.fork);
//			philo->r_fork.state = 1;
//			philo->l_fork.state = 1;
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
//	philo->r_fork.state = 0;
//	philo->l_fork.state = 0;
	pthread_mutex_unlock(philo->r_fork.fork);
	pthread_mutex_unlock(philo->l_fork.fork);
}
