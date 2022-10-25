/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 10:48:23 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ethics.h"

void *ft_philosopher(void *dining_room)
{
	(void)dining_room;
	printf("entrei\n");
	return NULL;
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
	t_dining_room	*dining_room;
	int		i;

	dining_room = malloc(sizeof(t_dining_room));
	dining_room->philos = malloc(sizeof(pthread_t) * config->number_of_philosophers);
	if (!dining_room->philos)
		return ;
	dining_room->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	if (!dining_room->forks)
		return ;
	i = -1;
	while (++i < config->number_of_philosophers)
		pthread_mutex_init(&dining_room->forks[i], NULL);
	i = -1;
	while (++i < config->number_of_philosophers) // devo tratar os possiveis erros de criarção de threads e mutex?
		pthread_create(&dining_room->philos[i], NULL, ft_philosopher, (void *)&dining_room);
	i = -1;
	while (++i < config->number_of_philosophers)
		pthread_join(*dining_room->philos, NULL);
	return ;
}

int	main(int argc, char *argv[])
{
	t_conf				config;
	
	if (argc == 5 || argc == 6)
		default_imput(argv, argc, &config);
	else
		return (0);
	ft_philosophy(&config);


	return (0);
}
