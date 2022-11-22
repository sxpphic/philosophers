/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:48:07 by vipereir          #+#    #+#             */
/*   Updated: 2022/11/22 17:35:11 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	ft_init_forks(t_logic *logic)
{
	int	i;

	i = -1;
	while(++i < logic->number_phi)
	{
		if (pthread_mutex_init(&logic->forks[i], NULL) != 0)
			return (-1);
	}
	return (0);
}

int	smart_sleep(long	time, t_phi *phis)
{
	register int	i;

	(void)phis;
	i = time / 1000;
	while (i)
	{
		usleep(1000);
		i--;
	//	if (phis->death == 1)
	//	{
	//		printf("%ld %i died\n", get_time(), phis->index + 1);
	//		return(1);
	//	}
	}
	return (0);
}

void	take_forks(t_phi *phis)
{
	while ((phis->logic->is_fork_locked[phis->index] == 0 && phis->logic->is_fork_locked[phis->index - 1] == 0) || (phis->logic->is_fork_locked[phis->index] == 0 && phis->logic->is_fork_locked[phis->logic->number_phi -1] == 0))
	{
		if (!phis->logic->is_fork_locked[phis->index])
		{
			printf("%ld %i has taken a fork\n", get_time(), phis->index + 1);
			pthread_mutex_lock(&phis->logic->forks[phis->index]);
			phis->logic->is_fork_locked[phis->index] = 1;
		}
		if (phis->index == 0)
		{
			if (!phis->logic->is_fork_locked[phis->logic->number_phi -1])
			{
				pthread_mutex_lock(&phis->logic->forks[phis->logic->number_phi - 1]);
				phis->logic->is_fork_locked[phis->logic->number_phi -1] = 1;
				printf("%ld %i has taken a fork\n", get_time(), phis->index + 1);
			}
		}
		else
		{
			if (!phis->logic->is_fork_locked[phis->index - 1])
			{
				pthread_mutex_lock(&phis->logic->forks[phis->index - 1]);
				phis->logic->is_fork_locked[phis->index - 1] = 1;
				printf("%ld %i has taken a fork\n", get_time(), phis->index + 1);
			}
		}
	}
}

void	ft_eat(t_phi	*phis)
{
	long	eat;
	eat = get_time();
	phis->last_eat = eat;
	printf("%ld %i is eating\n", eat, phis->index + 1);
	usleep(phis->logic->t_eat);
	pthread_mutex_unlock(&phis->logic->forks[phis->index]);
	if (phis->index == 0)
		pthread_mutex_unlock(&phis->logic->forks[phis->logic->number_phi - 1]);
	else
		pthread_mutex_unlock(&phis->logic->forks[phis->index - 1]);
}

void	ft_sleep(t_phi *phis)
{
	printf("%ld %i is sleeping\n", get_time(), phis->index + 1);
	usleep(phis->logic->t_slp);
}

void	ft_think(t_phi *phis)
{
	printf("%ld %i is thinking\n", get_time(), phis->index + 1);
}

void	*ft_philosopher(void	*arg)
{
	t_phi	*phis;

	phis = (t_phi*)arg;
	while (1)
	{
		take_forks(phis);
		ft_eat(phis);
		ft_sleep(phis);
		ft_think(phis);
	}
	return (NULL);
}

int	ft_philo_create(t_logic *logic, t_phi **philoo)
{
	int	i;
	t_phi	*phis;

	phis = (*philoo);

	i = -1;
	while (++i < logic->number_phi)
	{
		phis[i].index = i;
		phis[i].logic = logic;
		phis[i].last_eat = get_time();
	}

	i = 0;
	while (i < logic->number_phi)
	{
		if (pthread_create(&logic->philos[i], NULL, ft_philosopher, (void *)&phis[i])!= 0)
			return (-2);
		i++;
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

int	ft_destroy_forks(t_logic *logic)
{
	int	i;

	i = -1;
	while(++i < logic->number_phi)
	{
		if (pthread_mutex_destroy(&logic->forks[i]) != 0)
			return (-1);
	}
	return (0);
}

void	ft_cleaning(t_logic *logic, t_phi **phis)
{
	free(logic->philos);
	free(logic->forks);
	free(*phis);
}

int	ft_check_imputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
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

long	get_time(void) // será q ta malfeito isso ?? to tentando usar menos processamento mas parece feio dms, o certo ceria multiplicar o sec por 1000 e dps somar eles;
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*ft_seeker(void	*arg)
{
	t_phi	*phis;
	long	time_die;
	long	time;

	phis = (t_phi*)arg;

	time_die = phis->logic->t_die / 1000;
//	usleep(phis->logic->t_die + 10000);
	while (1)
	{
		time = get_time();
		if (time - phis->last_eat > time_die)
		{
			printf("diff: %ld\n", time - phis->last_eat);
			printf("%ld %i died\n", time, phis->index + 1);
			exit(0);
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_logic			logic;
	t_phi			*phis;
	pthread_t		*seeker;

	if (ft_check_imputs(argv) != 0) //valida se há somente números no imput
		return (ft_error("imput error"));
	memset(&logic, 0x0, sizeof(t_logic));
	if (argc == 5 || argc == 6)
		set_imput(argc, argv, &logic); // seta os imputs na struct
	else
		return (ft_error("wrong imput"));

	seeker = malloc(sizeof(pthread_t) * logic.number_phi);
	if (ft_malloc_zero(&logic, &phis) != 0) // malloc em tudo
		return (ft_error("malloc error"));

	if (ft_init_forks(&logic) != 0) // crio os garfos
		return (ft_error("forks error"));


	if (ft_philo_create(&logic, &phis) != 0) // crio os philosophers
		return (ft_error("thread error"));

	int	i;
	i = -1;
//	usleep(logic.t_die);
	while (++i < logic.number_phi)
		pthread_create(&seeker[i], NULL, ft_seeker, &phis[i]);



	if (ft_wait_philo(&logic) != 0) // espero os philosophers terminarem
		return (ft_error("join error"));

	if (ft_destroy_forks(&logic) != 0) // destroi os garfos
		return (ft_error("forks_d error"));

	ft_cleaning(&logic, &phis); // da free nos garfos e filósofos

	return (0);
}

/*int	main(void)
{
	printf("%ld\n", get_time());
	usleep();
	printf("%ld\n", get_time());
	return (0);
}*/
