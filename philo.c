/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:38:12 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 02:12:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_philo(t_master *master, t_philo *philo)
{
	int		i;

	i = 0;
	master->philo = philo;
	master->phmaxeat = 0;
	master->end = 0;
	master->start_time = getstart_time();
	while (i++ < master->nbphilo)
	{
		philo[i].last_meal = getstart_time();
	}
	if (ft_create_threads(master, philo) == 1)
		return (1);
	//faire un check death
	return (0);
}

int	link_philo_forks(int i, t_master *master, t_philo *philo)
{
	if (i == 0)
	{
		philo[i].lfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		philo[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		//philo[i].mutex_rfork = philo[1].mutex_lfork;
		//philo[i].mutex_lfork = philo[master->nbphilo -1].mutex_rfork;
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
		philo[i].rfork = philo[i + 1].lfork;
		philo[i].lfork = philo[i -1].rfork;
	}
	return (0);
}

/*
void	battle_for_forks(t_philo *philo)
{

}*/
