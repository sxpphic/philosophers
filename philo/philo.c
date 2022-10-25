/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 10:04:45 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ethics.h"

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

long int	time_diff(struct timeval *start, struct timeval *end)
{
	long int c;

	c = (end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec) / 1000;
	if (c < 0)
		c += 1000;
	return (c);
}

void	default_imput(char **argv, int argc, t_conf *config)
{
	config->number_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]) * 1000;
	config->time_to_eat = ft_atoi(argv[3]) * 1000;
	config->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		config->number_of_time_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void	ft_philosophy(t_conf *config)
{
	
}

int	main(int argc, char *argv[])
{
	struct timeval		start;
	struct timeval		end;
	t_conf				config;
	long long			timestamp;
	
	if (argc == 5 || argc == 6)
		default_imput(argv, argc, &config);
	else
		return (0);
	timestamp = 0;
	//ft_philosophy(&default_imput);
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	printf("%li take fork\n", time_diff(&start, &end));
	gettimeofday(&start, NULL);
	usleep(config.time_to_eat);
	gettimeofday(&end, NULL);
	timestamp += time_diff(&start, &end);
	printf("%lli take fork\n", timestamp);
	gettimeofday(&start, NULL);
	usleep(config.time_to_eat);
	gettimeofday(&end, NULL);
	timestamp += time_diff(&start, &end);
	printf("%lli take fork\n", timestamp);


	return (0);
}
