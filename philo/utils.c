/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:11:55 by vipereir          #+#    #+#             */
/*   Updated: 2022/12/06 16:04:30 by vipereir         ###   ########.fr       */
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

int	ft_malloc_zero(t_table *table, t_logic *logic, t_phi **phis)
{
	*phis = malloc(sizeof(t_phi) * logic->number_phi);
	table->philos = malloc(sizeof(pthread_t) * logic->number_phi);
	if (!table->philos)
		return (-1);
	table->forks = malloc(sizeof(pthread_mutex_t) * logic->number_phi);
	if (!table->forks)
		return (-1);
	return (0);
}

int	ft_error(char *s)
{
	printf("%s\n", s);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e6) + (time.tv_usec));
}

int	ft_check_imputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argv[i][j] == '0')
		return (-1);
	while (argv[i])
	{
		if (argv[i][j] == '-')
			return (-1);
		else if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] >= 0x30 && argv[i][j] <= 0x39)
				j++;
			else
				return (-1);
		}
		j = 0;
		i++;
	}
	return (0);
}

void	ft_cleaning(t_table *table, t_phi **phis)
{
	free(table->philos);
	free(table->forks);
	free(*phis);
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

int	ft_init_forks(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (-1);
	while (++i < logic->number_phi)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (-1);
	}
	return (0);
}

int	ft_philo_init(t_table *table, t_logic *logic, t_phi **philos)
{
	int		i;
	t_phi	*phis;

	phis = (*philos);
	i = 0;
	while (i < logic->number_phi)
	{
		if (pthread_create(&table->philos[i], NULL, ft_philosopher, &phis[i]))
			return (-2);
		i += 2;
	}
	i = 1;
	while (i < logic->number_phi)
	{
		if (pthread_create(&table->philos[i], NULL, ft_philosopher, &phis[i]))
			return (-2);
		i += 2;
	}
	return (0);
}

int	ft_philo_create(t_table *table, t_logic *logic, t_phi **philos)
{
	int		i;
	t_phi	*phis;

	phis = (*philos);
	table->end = 0;
	i = -1;
	while (++i < logic->number_phi)
	{
		phis[i].id = i;
		if (i > 0)
			phis[i].l_fork = &table->forks[i - 1];
		else
			phis[i].l_fork = &table->forks[logic->number_phi - 1];
		phis[i].philo = &table->philos[i];
		phis[i].r_fork = &table->forks[i];
		phis[i].n_eats = 0;
		phis[i].end = &table->end;
		phis[i].last_eat = get_time();
		(*philos)[i].print = &table->print;
		phis[i].logic = logic;
	}
	if (ft_philo_init(table, logic, philos))
		return (-2);
	return (0);
}

int	ft_wait_philo(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	while (++i < logic->number_phi)
	{
		if (pthread_join(table->philos[i], NULL) != 0)
			return (-3);
	}
	return (0);
}

int	ft_destroy_forks(t_table *table, t_logic *logic)
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&table->print) != 0)
		return (-1);
	while (++i < logic->number_phi)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (-1);
	}
	return (0);
}

void	mutex_print(t_phi *philo, char *s)
{
	if (!*philo->end)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld %i %s\n", get_time() / 1000, philo->id + 1, s);
		pthread_mutex_unlock(philo->print);
	}
}
