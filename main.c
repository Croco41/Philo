/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:39:32 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 02:10:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_master *master, t_philo *philo)
{
	int i;
	int ide;

	ide = 1;
	i = -1;

	while (++i < master->nbphilo)
	{
		philo[i].id = ide++;
		philo[i].last_meal = 0;
		philo[i].nbr_meal = 0;
		//prendre fourchette?
	}
	return (0);
}

int	ft_create_threads(t_master *master, t_philo *philo)
{
	int i;

	i= -1;
	while (++i < master->nbphilo)
	{
	if (pthread_create(&(philo[i].philo), NULL, &routine, NULL) != 0)
		return (1);
	}
	i = -1
	while (++i < master->nbphilo)
	{
		if (pthread_join(philo[i].philo, NULL) != 0)
			return (1);
	}
	return (0);
}

char *parsing(int ac, char **av, t_master *master)
{
	if (ac < 5 && ac > 6)
		return ("error: philo must have 4 or 5 arguments");
	master->nbphilo = ft_atoi(av[1]);
	if (master->nbphilo < 1)
		return ("error: we need at least 2 philosophers");
	master->tdie = ft_atoi(av[2]);
	if (master->tdie < 1)
		return ("error: arg 2 must be <time to die>");
	master->teat = ft_atoi(av[3]);
	if (master->teat < 1)
                return ("error: arg 3 must be <time to eat>");
	master->tsleep = ft_atoi(av[4]);
        if (master->tsleep < 1)
                return ("error: arg 4 must be <time to sleep>");
	master->maxeat = -1;
	if (ac == 6)
	{
		master->maxeat = ft_atoi(av[5]);
		if (master->maxeat < 1)
			return ("error: arg 5 must be <number of times must eat>");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_master *master;
	t_philo *philo;
	master = (t_master *)malloc(sizeof(t_master));
	if (!master)
		return (1);
	if (parse(ac, av, master))
		return (ft_quit_free(master, philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * master->nbphilo);
	if (!philo)
		return(ft_quit_free(master, philo);
	if (ft_init_philo(master, philo))
		return (ft_quit_free(master, philo);
	if (ft_start_philo(master, philo))
		return (ft_quit_free(master, philo);
	ft_free_philo(master, philo);
	ft_destroy_all(master, philo);
	return (0);

	// faut initier les philos...
	// faut démarrer les philos /threads
	// faut terminier les threads, free philo...

}
