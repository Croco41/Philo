/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:38:12 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 02:07:47 by user42           ###   ########.fr       */
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

		if ()
			return (1);
	}

	else if (i == master->nbphilo - 1)
	{

	}

	else
}
