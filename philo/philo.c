/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/10 11:44:54 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophia.h"

void *print_test(void *a)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		printf("%i\n", i);
		usleep(100);
		i++;
	}
	return (NULL);
}

void	t_error(char *msg)
{
	ft_printf("%mgs\n");
	exit(1);
}

int	main(void)
{
	pthread_t	philo[number_of_philosophers];
	void	*result;
	int i;

	i = -1;
	while (i++ < number_of_philosophers)
	{
		if (pthread_create(&philo[i], NULL, print_test, NULL) == -1)
			t_error("pthread create error!");
	}
	i = -1;
	while 


	return (0);
}
