/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seeker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:41:50 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 12:52:48 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_everybody_eats(t_phi *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].logic->number_phi)
	{
		pthread_mutex_lock(philos[i].m_num_eat);
		if (philos[i].n_eats >= philos[i].logic->number_eat)
		{
			pthread_mutex_unlock(philos[i].m_num_eat);
			i++;
		}
		else
		{
			pthread_mutex_unlock(philos[i].m_num_eat);
			return (0);
		}
		if (i == philos[0].logic->number_phi)
			break ;
	}
	return (1);
}

int	ft_died(t_phi *philos, int i, long time)
{
	pthread_mutex_unlock(philos[i].m_last_eat);
	pthread_mutex_lock(philos[i].m_end);
	*philos[i].end = 1;
	pthread_mutex_unlock(philos[i].m_end);
	usleep(200);
	pthread_mutex_lock(philos[i].print);
	printf("%ld %i %s\n", time / 1000, philos[i].id + 1, "died");
	pthread_mutex_unlock(philos[i].print);
	return (1);
}

int	check_end(t_phi *philos, int i)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(philos[i].m_last_eat);
	if (time - philos[i].last_eat > philos[0].logic->t_die)
		return (ft_died(philos, i, time));
	else
		pthread_mutex_unlock(philos[i].m_last_eat);
	if (philos[i].logic->number_eat && ft_everybody_eats(philos))
	{
		pthread_mutex_lock(philos[i].m_end);
		*philos[i].end = 1;
		pthread_mutex_unlock(philos[i].m_end);
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
