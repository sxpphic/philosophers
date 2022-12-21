/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:53:45 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 10:30:44 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_forks(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->m_last_eat, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->m_end, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->m_num_eat, NULL) != 0)
		return (-1);
	while (++i < logic->number_phi)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (-1);
	}
	return (0);
}

int	ft_philo_init(t_table *table, t_logic *logic, t_phi **philos)
{
	int		i;
	t_phi	*phis;

	phis = (*philos);
	i = 0;
	while (i < logic->number_phi)
	{
		if (pthread_create(&table->philos[i], NULL, ft_philosopher, &phis[i]))
			return (-2);
		i += 2;
		usleep(10);
	}
	i = 1;
	while (i < logic->number_phi)
	{
		if (pthread_create(&table->philos[i], NULL, ft_philosopher, &phis[i]))
			return (-2);
		i += 2;
		usleep(10);
	}
	return (0);
}

void	set_philo_data(t_table *table, t_logic *logic, t_phi **philos, int i)
{
	t_phi	*phis;

	phis = (*philos);
	phis[i].id = i;
	if (i > 0)
		phis[i].l_fork.fork = &table->forks[i - 1];
	else
		phis[i].l_fork.fork = &table->forks[logic->number_phi - 1];
	phis[i].philo = &table->philos[i];
	phis[i].r_fork.fork = &table->forks[i];
	phis[i].r_fork.state = 0;
	phis[i].l_fork.state = 0;
	phis[i].n_eats = 0;
	phis[i].end = &table->end;
	phis[i].last_eat = get_time();
	phis[i].print = &table->print;
	phis[i].m_end = &table->m_end;
	phis[i].m_last_eat = &table->m_last_eat;
	phis[i].m_num_eat = &table->m_num_eat;
	phis[i].logic = logic;
}

int	ft_philo_create(t_table *table, t_logic *logic, t_phi **philos)
{
	int		i;

	table->end = 0;
	i = -1;
	while (++i < logic->number_phi)
		set_philo_data(table, logic, philos, i);
	if (ft_philo_init(table, logic, philos))
		return (-2);
	return (0);
}

int	ft_wait_philo(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	while (++i < logic->number_phi)
	{
		if (pthread_join(table->philos[i], NULL) != 0)
			return (-3);
	}
	return (0);
}
