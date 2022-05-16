/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:38:12 by user42            #+#    #+#             */
/*   Updated: 2022/05/17 01:09:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_philo(t_master *master, t_philo *philo)
{
	int		i;

	i = -1;
	master->iofp = 0;
	master->philo = philo;
	master->phmaxeat = 0;
	master->end = 0;
	master->start_time = getstart_time();
	while (++i < master->nbphilo)
	{
		philo[i].last_meal = getstart_time();
	}
	if (ft_create_threads(master, philo) == 1)
		return (1);
	return (0);
}

int	link_philo_forks(int i, t_master *master, t_philo *philo)
{
	if (!i)
	{
		philo[i].lfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		philo[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[i].lfork || pthread_mutex_init(philo[i].lfork, NULL)
			|| !philo[i].rfork || pthread_mutex_init(philo[i].rfork, NULL))
			return (1);
	}
	else if (i == master->nbphilo - 1)
	{	
		philo[i].rfork = philo[0].lfork;
		philo[i].lfork = philo[i - 1].rfork;
	}
	else
	{	
		philo[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		philo[i].lfork = philo[i -1].rfork;
		if (!philo[i].rfork || pthread_mutex_init(philo[i].rfork, NULL))
			return (1);
	}
	return (0);
}
