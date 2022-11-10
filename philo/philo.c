/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/10 17:08:58 by vipereir         ###   ########.fr       */
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
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
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

int	ft_malloc_zero(t_logic *logic)
{
	logic->philos = malloc(sizeof(pthread_t) * logic->number_phi);
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

int	ft_init_forks(t_logic *logic)
{
	int	i;

	i = -1;
	while(++i < logic->number_phi)
	{
		if (pthread_mutex_init(&logic->forks[i], NULL) != 0)
		{
			printf("mutex_error\n");
			return (-1);
		}
	}
	return (0);
}

void	*ft_philosopher(void	*arg)
{
	printf("plato\n");
	return (NULL);
}

int	ft_philo_create(t_logic *logic)
{
	int	i;

	i = -1;
	while (++i < logic->number_phi)
	{
		if (pthread_create(&logic->philos[i], NULL, ft_philosopher, NULL) != 0)
			return (-2);
	}
	return (0);
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

int	ft_wait_philo(t_logic *logic)
{
	int	i;

	i = -1;
	while (++i < logic->number_phi)
	{
		if (pthread_join(logic->philos[i], NULL) != 0)
			return (-3);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_logic			logic;

	memset(&logic, 0x0, sizeof(t_logic));
	if (argc == 5 || argc == 6)
		set_imput(argc, argv, &logic);
	else
		return (ft_error("wrong imput"));

	if (ft_malloc_zero(&logic) != 0) // malloc em tudo
		return (ft_error("malloc error"));

	if (ft_init_forks(&logic) != 0) // crio os garfos
		return (ft_error("forks error"));

	if (ft_philo_create(&logic) != 0) // crio os philosophers
		return (ft_error("thread error"));

	if (ft_wait_philo(&logic) != 0) // espero os philosophers terminarem
		return (ft_error("join error"));

return (0);
}
