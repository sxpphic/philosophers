/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 11:23:23 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ethics.h"

void	ft_think(int philo_id)
{
	printf("timestamp_in_ms %i is thinking\n", philo_id);
}

void *ft_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_think(philo->phiid);
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
	t_philo			*philos;
	int				i;

	philos = malloc(sizeof(t_philo) * config->number_of_philosophers);
	dining_room = malloc(sizeof(t_dining_room)); //esse malloc me salvou, segfalta sem ele.
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
	while (++i < config->number_of_philosophers) // cria os philosophers na struct philo
	{
		philos[i].phiid = i + 1;
		if (i == 0)
			philos[i].left_fork = &dining_room->forks[config->number_of_philosophers - 1];
		else
			philos[i].left_fork = &dining_room->forks[i - 1];
		philos[i].philo = &dining_room->philos[i];
		philos[i].right_fork = &dining_room->forks[i];
	}
	i = -1;
	while (++i < config->number_of_philosophers) // devo tratar os possiveis erros de criarção de threads e mutex?
		pthread_create(&dining_room->philos[i], NULL, ft_philosopher, (void *)&philos[i]);
	i = -1;
	while (++i < config->number_of_philosophers)
		pthread_join(dining_room->philos[i], NULL);
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
