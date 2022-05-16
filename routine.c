/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:12:25 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 18:18:34 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	waiting(t_master *master, size_t b, size_t c)
{

	while ((getstart_time() - b) < c)
	{
		pthread_mutex_lock(master->locktime);	
		if (master->end)
		{
			pthread_mutex_unlock(master->locktime);	
			return (-1);
		}
		pthread_mutex_unlock(master->locktime);	
		usleep(100);
	}
	return (0);
}

size_t	getstart_time(void)
{
	struct timeval	current;
	size_t			time;

	if (gettimeofday(&current, NULL) != 0)
		return (1);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

void	*routine(void *arg)
{
	t_master	*master;
	t_philo		*philo;
	int			iofp;

	master = (t_master *)arg;
	iofp = master->iofp;
	master->iofp++;
	philo = master->philo;

	pthread_mutex_lock(master->locktime);	
	master->start_time = getstart_time();
	pthread_mutex_unlock(master->locktime);	
	if (master->iofp % 2 != 0 && master->nbphilo != 1)
		waiting(master, master->start_time, 15);
	while (1)
	{
		if (ft_parsing_actions(master, philo, iofp) == 1)
			break ;
	}
	return (NULL);
}
