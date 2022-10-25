/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 10:29:58 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ethics.h"

void *ft_philosopher(void *fork)
{

	return (NULL);
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
	pthread_t			*philos;
	pthread_mutex_t		*forks;
	int					i;

	philos = malloc(sizeof(pthread_t) * config->number_of_philosophers);
	if (!philos)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < config->number_of_philosophers)
		pthread_mutex_init(&forks[i]);
	i = -1;
	while (++i < config->number_of_philosophers) // devo tratar os possiveis erros de criarção de threads e mutex?
		pthread_create(&philos[i], NULL, ft_philosopher, (void *)&fork[i]);
	while (i < config->number_of_philosophers)
}

int	main(int argc, char *argv[])
{
	t_conf				config;
	
	if (argc == 5 || argc == 6)
		default_imput(argv, argc, &config);
	else
		return (0);
	ft_philosophy(&default_imput);


	return (0);
}
