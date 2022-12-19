/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:56:59 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 10:34:03 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_imputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argv[i][j] == '0')
		return (-1);
	while (argv[i])
	{
		if (argv[i][j] == '-')
			return (-1);
		else if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] >= 0x30 && argv[i][j] <= 0x39)
				j++;
			else
				return (-1);
		}
		j = 0;
		i++;
	}
	return (0);
}

void	ft_cleaning(t_table *table, t_phi **phis)
{
	free(table->philos);
	free(table->forks);
	free(*phis);
}

void	set_imput(int argc, char *argv[], t_logic *logic)
{
	logic->number_phi = ft_atoi(argv[1]);
	logic->t_die = ft_atoi(argv[2]) * 1000;
	logic->t_eat = ft_atoi(argv[3]) * 1000;
	logic->t_slp = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		logic->number_eat = ft_atoi(argv[5]);
}

int	ft_destroy_forks(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&table->print) != 0)
		return (-1);
	while (++i < logic->number_phi)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (-1);
	}
	return (0);
}

void	mutex_print(t_phi *philo, char *s)
{
	pthread_mutex_lock(philo->m_end);
	if (!*philo->end)
	{
		pthread_mutex_unlock(philo->m_end);
		pthread_mutex_lock(philo->print);
		printf("%ld %i %s\n", get_time() / 1000, philo->id + 1, s);
		pthread_mutex_unlock(philo->print);
	}
	else
		pthread_mutex_unlock(philo->m_end);
}
