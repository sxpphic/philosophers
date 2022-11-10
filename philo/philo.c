/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/10 14:34:24 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_malloc_zero(t_logic *logic)
{
	logic = malloc(sizeof(t_logic *));
	if (!logic)
		return (-1);
	logic->philos = malloc(sizeof(pthread_t) * logic->number_phi);
	if (!logic->philos)
		return (-1);
	logic->forks = malloc(sizeof(pthread_mutex_t) * logic->number_phi);
	if (!logic->forks)
		return (-1);
	memset(logic, 0x0, sizeof(t_logic));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_logic			logic;

	if (ft_malloc_zero(&logic) == -1)
	{
		printf("malloc_error\n");
		return (0);
	}


return (0);
}
