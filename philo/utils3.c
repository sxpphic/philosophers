/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:27:54 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/19 10:29:44 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_int(char	**argv)
{
	int		i;
	long	nb;

	i = 1;
	while (argv[i])
	{
		nb = ft_atoi(argv[i]);
		if ((nb > 2147483647) || (nb < -2147483648))
			return (-1);
		else
			i++;
	}
	return (0);
}

int	check_inputs(int argc, char *argv[], t_logic *logic)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_check_int(argv) != 0)
			return (!ft_error("imput error"));
		if (ft_check_imputs(argv) != 0)
			return (!ft_error("imput error"));
		memset(logic, 0x0, sizeof(t_logic));
		set_imput(argc, argv, logic);
	}
	else
		return (!ft_error("wrong imput"));
	return (0);
}

int	s_sleep(t_phi *philo, unsigned long time)
{
	long	t;

	t = get_time() + time / 1;
	while (get_time() < t)
	{
		pthread_mutex_lock(philo->m_end);
		if (*philo->end)
		{
			pthread_mutex_unlock(philo->m_end);
			return (1);
		}
		else
			pthread_mutex_unlock(philo->m_end);
		usleep(1000);
	}
	return (0);
}
