/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 09:21:56 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophia.h"

typedef struct s_conf {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_each_philosopher_must_eat;
}t_conf;

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

void *test_func(void *a)
{
	int	i;
	long c;

	c = (long)a;
	i = -1;
	while (i++ < 5)
	{
		c++;
		printf("%li\n", c);
	}
	return ((void *)c);
}



void	default_imput(char **argv, int argc, t_conf *config)
{
	config->number_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->number_of_time_each_philosopher_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_conf				config;
	int					i;
	struct timeval		start;
	struct timeval		end;
	long long time_ms;
	long long time_sec;
	long long time_start_sec;
	long long time_start_ms;
	
	if (argc == 5 || argc == 6)
		default_imput(argv, argc, &config);
	else
		return (0);
	time_ms = 0;
	printf("time: %lli\n", time_ms);
	gettimeofday(&start, NULL);
	usleep(100 * 1000);
	gettimeofday(&end, NULL);
	time_ms = /*(end.tv_sec - start.tv_sec) +*/ (end.tv_usec - start.tv_usec) / 1000;
	if (time_ms < 0)
	{
		time_ms += 1000;
		printf("asdfadsf\n");
	}
	printf("time: %lli\n", time_ms);
	i = 1;
/*	while (i > 0)
	{
		gettimeofday(&time_count, &time_zone);
		time_ms = time_count.tv_usec / 1000;
		time_sec = time_count.tv_sec - time_start_sec;
		printf("time: %lli\n", time_sec * 1000);
		printf("time: %lli\n", time_ms);
		i++;
		usleep(10 * 1000);
	}
	*/
	return (0);
}
