/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:11:55 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/22 14:52:55 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	signal;

	i = 0;
	nb = 0;
	signal = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = signal * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb + (str[i] - '0');
		i++;
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10;
	}
	return (nb);
}

int	ft_malloc_zero(t_logic *logic, t_phi **phis)
{
	*phis = malloc(sizeof(t_phi) * logic->number_phi);
	logic->philos = malloc(sizeof(pthread_t) * logic->number_phi);
	logic->is_fork_locked = malloc(sizeof(int) * logic->number_phi);
	if (!logic->philos)
		return (-1);
	logic->forks = malloc(sizeof(pthread_mutex_t) * logic->number_phi);
	if (!logic->forks)
		return (-1);
	return (0);
}

int	ft_error(char *s)
{
		printf("%s\n", s);
		return (0);
}
