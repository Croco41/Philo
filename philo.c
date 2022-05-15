/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:38:12 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 16:03:15 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int 	ft_start_philo(t_master *master, t_philo *philo)
{
	int 	i;

	i = 0;
	master->dead = -1;
	master->start_time = getstart_time();
	while (i++ < master->nbphilo)
	{
		philo[i].teat = getstart_time();
	}
	if (ft_create_threads(master, philo) == 1)
		return (1);
	//faire un check death
	return (0);
}

int	assign_forks(int i, t_master *master, t_philo *philo)
{
	if (i == 0)
	{
		philo[i].mutex_rfork = philo[1].mutex_lfork;
		philo[i].mutex_lfork = philo[master->nbphilo -1].mutex_rfork;
		//if (pthread_mutex_init(philo[i].mutex_lfork, NULL) || pthread_mutex_init(philo[i].mutex_rfork, NULL))
		//	return (1);
	}

	else if (i == master->nbphilo - 1)
	{	
		philo[i].mutex_rfork = philo[0].mutex_lfork;
		philo[i].mutex_lfork = philo[i - 1].mutex_rfork;
	}
	else
	{	
		philo[i].mutex_rfork = philo[id + 1].mutex_lfork;
		philo[i].mutex_lfork = philo[id -1].mutex_rfork;
	}
	return (0);
}

void	battle_for_forks(t_philo *philo)
{

}
