/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/17 13:19:32 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_onephilo(t_master *master, t_philo *philo, int i)
{
	if (waiting(master, (int)getstart_time(), master->tdie) == 1)
	{
		pthread_mutex_unlock(philo[i].lfork);
		pthread_mutex_unlock(philo[i].rfork);
		return (1);
	}
	pthread_mutex_unlock(philo[i].lfork);
	pthread_mutex_unlock(philo[i].rfork);
	return (1);
}

int	ft_philo_fight_foreat(t_master *master, t_philo *philo, int i)
{
	order_lock_forkeat(i, master, philo);
	ft_print_actions(master, i, "has taken a fork\n");
	if (master->nbphilo == 1)
		return (ft_onephilo(master, philo, i));
	ft_print_actions(master, i, "has taken a fork\n");
	ft_print_actions(master, i, "is eating\n");
	pthread_mutex_lock(master->locktime);
	philo[i].last_meal = getstart_time();
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat)
		master->phmaxeat++;
	pthread_mutex_unlock(master->locktime);
	if (waiting(master, (int)getstart_time(), master->teat) == 1)
	{
		pthread_mutex_unlock(philo[i].lfork);
		pthread_mutex_unlock(philo[i].rfork);
		return (1);
	}
	pthread_mutex_unlock(philo[i].lfork);
	pthread_mutex_unlock(philo[i].rfork);
	return (0);
}	

int	ft_you_are_dead(t_master *master, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < master->nbphilo)
	{	
		pthread_mutex_lock(master->locktime);
		if ((int)getstart_time() - (int)philo[i].last_meal > master->tdie)
		{
			master->dead = 1;
			pthread_mutex_unlock(master->locktime);
			ft_print_actions(master, i, "died\n");
			return (1);
		}
		if (master->maxeat != -1 && master->phmaxeat >= master->nbphilo)
		{
			master->end = 1;
			pthread_mutex_unlock(master->locktime);
			return (1);
		}
		else
			pthread_mutex_unlock(master->locktime);
		i++;
	}
	return (0);
}

int	ft_philo_sleep(t_master *master, int i)
{
	ft_print_actions(master, i, "is sleeping\n");
	if (waiting(master, (int)getstart_time(), master->tsleep))
		return (1);
	return (0);
}

/*void	ft_philo_thinking(t_master *master, int i)
{
	ft_print_actions(master, i, "is thinking\n");
//	usleep(master->tthink);
}*/

int	ft_parsing_actions(t_master *master, t_philo *philo, int i)
{
	if (ft_philo_fight_foreat(master, philo, i))
		return (1);
	if (ft_philo_sleep(master, i))
		return (1);
	//ft_philo_thinking(master, i);
	ft_print_actions(master, i, "is thinking\n");
	if (master->maxeat != -1 && philo[i].nbr_meal >= master->maxeat)
		return (1);
	//if (master->end == 1)
	//	return (1);
	return (0);
}
