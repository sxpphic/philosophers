/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/10 11:40:15 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_args(t_logic *logic)
{
	printf("%d\n", logic->number_phi);
	printf("%d\n", logic->t_die);
	printf("%d\n", logic->t_eat);
	printf("%d\n", logic->t_slp);
	printf("%d\n", logic->number_eat);
}

int	main(int argc, char *argv[])
{
	t_logic			logic;
	unsigned char	c;

	logic.t_eat = 0x1;
	print_args(&logic);
	memset(&logic, 0x0, sizeof(logic));
	print_args(&logic);
return (0);
}
