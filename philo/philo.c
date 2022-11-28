/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/28 11:05:12 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	take_forks(t_phi *phis)
{
}

void	ft_eat(t_phi	*phis)
{
}

void	ft_sleep(t_phi *phis)
{
	printf("%ld %i is sleeping\n", get_time(), phis->index + 1);
	usleep(phis->logic->t_slp);
}

void	ft_think(t_phi *phis)
{
	printf("%ld %i is thinking\n", get_time(), phis->index + 1);
}

void	*ft_philosopher(void	*arg)
{
	t_phi	*phis;

	phis = (t_phi*)arg;
	while (1)
	{
		take_forks(phis);
		ft_eat(phis);
		ft_sleep(phis);
		ft_think(phis);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	t_phi			*philos;
	t_logic			logic;

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
	if (ft_wait_philo(&table, &logic) != 0)
		return (ft_error("join error"));
	if (ft_destroy_forks(&table, &logic) != 0)
		return (ft_error("forks_d error"));
	ft_cleaning(&table, &philos);
	return (0);
}
