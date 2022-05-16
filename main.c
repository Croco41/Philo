/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:39:32 by user42            #+#    #+#             */
/*   Updated: 2022/05/17 01:02:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_master *master, t_philo *philo)
{
	int		i;

	i = -1;
	master->locktime = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!master->locktime || pthread_mutex_init(master->locktime, NULL))
		return (1);
	master->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!master->print || pthread_mutex_init(master->print, NULL))
		return (1);
	while (++i < master->nbphilo)
	{
		philo[i].last_meal = 0;
		philo[i].nbr_meal = 0;
		if (link_philo_forks(i, master, philo) == 1)
			return (1);
	}
	return (0);
}

int	ft_create_threads(t_master *master, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < master->nbphilo)
	{
		if (pthread_create(&(philo[i].philo), NULL, &routine, master) != 0)
			return (1);
	}
	i = -1;
	while (1)
	{
		if (ft_you_are_dead(master, philo) == 1 || master->end == 1)
			break ;
	}
	while (++i < master->nbphilo)
	{
		if (pthread_join(philo[i].philo, NULL) != 0)
			return (1);
	}
	return (0);
}

int	parsing(int ac, char **av, t_master *master)
{
	if (ac < 5 || ac > 6)
		return (printf("_error the number of parameters is not good\n"));
	master->nbphilo = ft_atoi(av[1]);
	if (master->nbphilo < 1)
		return (printf("error: we need at least 1 philo\n"));
	master->tdie = ft_atoi(av[2]);
	if (master->tdie < 1)
		return (printf("error: Parameter 2, time to die is invalid\n"));
	master->teat = ft_atoi(av[3]);
	if (master->teat < 1)
		return (printf("error: Parameter 3, time to eat is invalid\n"));
	master->tsleep = ft_atoi(av[4]);
	if (master->tsleep < 1)
		return (printf("error: Parameter 4, time to sleep, is invalid\n"));
	master->maxeat = -1;
	if (ac == 6)
	{
		master->maxeat = ft_atoi(av[5]);
		if (master->maxeat < 1)
			return (printf("error: arg 5 (opt) is: nbr of times must eat\n"));
	}
	master->dead = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_master	*master;
	t_philo		*philo;

	master = (t_master *)malloc(sizeof(t_master));
	if (!master)
		return (1);
	if (parsing(ac, av, master))
		return (ft_quit_free(master, NULL));
	master->tthink = (master->tdie - master->tsleep - master->teat) / 2;
	philo = (t_philo *)malloc(sizeof(t_philo) * master->nbphilo);
	if (!philo)
		return (ft_quit_free(master, NULL));
	if (ft_init_philo(master, philo))
		return (ft_quit_free(master, philo));
	if (ft_start_philo(master, philo))
		return (ft_quit_free(master, philo));
	ft_destroy_all(master, philo);
	return (0);
}
