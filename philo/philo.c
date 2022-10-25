/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/25 15:08:14 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ethics.h"

long int	time_diff(struct timeval *start, struct timeval *end)
{
	long int c;

	c = (end->tv_usec - start->tv_usec) / 1000;
	if (c < 0)
		c += 1000;
	return (c);
}

void	ft_think(t_philo *philo)
{
	printf("%lli %i is thinking\n", philo->config.time_ms, philo->phiid);
}

long long get_time(void)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);

	pthread_mutex_lock(&philo->config.timer);
	philo->config.time_ms = get_time();
	pthread_mutex_unlock(&philo->config.timer);
	printf("%lli %i has taken a fork\n", philo->config.time_ms, philo->phiid);
}

void	ft_eat(t_philo *philo)
{
	printf("%lli %i is eating\n", philo->config.time_ms, philo->phiid);
	usleep(philo->config.time_to_eat);

	pthread_mutex_lock(&philo->config.timer);
	philo->config.time_ms = get_time();
	pthread_mutex_unlock(&philo->config.timer);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	printf("%lli %i is sleeping\n", philo->config.time_ms, philo->phiid);
	usleep(philo->config.time_to_sleep);
	philo->config.time_ms = get_time();
}

void *ft_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
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
		philos[i].config = *config;
	}
	i = 0;
	while (i < config->number_of_philosophers) // devo tratar os possiveis erros de criarção de threads e mutex?
	{
		pthread_create(&dining_room->philos[i], NULL, ft_philosopher, (void *)&philos[i]);
		i += 2;
	}
	i = 1;
	while (i < config->number_of_philosophers) // devo tratar os possiveis erros de criarção de threads e mutex?
	{
		pthread_create(&dining_room->philos[i], NULL, ft_philosopher, (void *)&philos[i]);
		i += 2;
	}
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
	config.time_ms = 0;
	ft_philosophy(&config);


	return (0);
}
