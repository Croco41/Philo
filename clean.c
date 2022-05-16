/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:27:31 by user42            #+#    #+#             */
/*   Updated: 2022/05/17 01:01:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_quit_free(t_master *master, t_philo *philo)
{
	if (master)
		free(master);
	if (philo)
		free(philo);
	return (1);
}

int	ft_destroy_all(t_master *master, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < master->nbphilo)
	{
		if (!i)
		{
			pthread_mutex_destroy(philo[i].lfork);
			pthread_mutex_destroy(philo[i].rfork);
			free(philo[i].lfork);
			free(philo[i].rfork);
		}
		else if (i != master->nbphilo -1)
		{
			pthread_mutex_destroy(philo[i].rfork);
			free(philo[i].rfork);
		}
	}
	pthread_mutex_destroy(master->locktime);
	pthread_mutex_destroy(master->print);
	free(master->print);
	free(master->locktime);
	free(master);
	free(philo);
	return (0);
}
