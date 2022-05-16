/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:27:31 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 19:23:52 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_quit_free(t_master *master, t_philo *philo)
{
	if (master)
		free(master);
	if (philo)
		free(philo);
	return(1);	
}

/*int ft_free_philo(t_master *master, t_philo *philo)
{

}
*/

int ft_destroy_all(t_master *master, t_philo *philo)
{
	int i;

	i = 0;
	while (i < master->nbphilo)
	{
		if (!i)
		{
		pthread_mutex_destroy(philo[i].lfork);
		pthread_mutex_destroy(philo[i].rfork);
		pthread_mutex_destroy(philo[i].print);
		free(philo[i].lfork);
		free(philo[i].rfork);
		}
		else if (i != master->nbphilo -1)
		{
		pthread_mutex_destroy(philo[i].rfork);	
		free(philo[i].rfork);
		}
		i++;
	}
	pthread_mutex_destroy(master->locktime);
	free(philo[0].print);
	free(master->locktime);
	free(master);
	free(philo);
	return (0);
}
