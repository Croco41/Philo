/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/17 00:25:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// manger
// prendre une fourchette
// dormir
// penser
// truc global actions
//
/*void	ft_print_actions(t_master *master, t_philo *philo, int i, char *str)
{
	pthread_mutex_lock(philo[i].print);
	pthread_mutex_lock(master->locktime);
	if (master->dead != 1)
	{
		ft_putnbr(getstart_time() - master->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)i + 1);
		write(1, " ", 1);
		ft_putstr(str);
	}	
	else if (master->dead > 0 && master->end == 0) 
	{
		master->end = 1;
		ft_putnbr(getstart_time() - master->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)i + 1);
		write(1, " ", 1);
		ft_putstr(str);
	}
	pthread_mutex_unlock(master->locktime);
	pthread_mutex_unlock(philo[i].print);
}*/

int	ft_onephilo(t_master *master, t_philo *philo, int i)
{
	if (master->nbphilo == 1)
	{
		if (waiting(master, (int)getstart_time(), master->tdie) == 0)
		{
			//master->dead = 1;	
			pthread_mutex_unlock(philo[i].rfork);
			pthread_mutex_unlock(philo[i].lfork);
			return (1);
		}
	}
	return (0);
}

int	ft_philo_fight_foreat(t_master *master, t_philo *philo, int i)
{
	pthread_mutex_lock(philo[i].lfork);
	pthread_mutex_lock(philo[i].rfork);
	ft_print_actions(master, philo, i, "has taken a fork\n");
	if (master->nbphilo == 1)
		return (ft_onephilo(master, philo, i));
	ft_print_actions(master, philo, i, "has taken a fork\n");
	ft_print_actions(master, philo, i, "is eating\n");
	pthread_mutex_lock(master->locktime);
	philo[i].last_meal = getstart_time();
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat)
		master->phmaxeat++;	
	pthread_mutex_unlock(master->locktime);
	if (waiting(master, (int)getstart_time(), master->teat) == 1)
	{
		pthread_mutex_unlock(philo[i].rfork);
		pthread_mutex_unlock(philo[i].lfork);
		return (1);
	}
	pthread_mutex_unlock(philo[i].rfork);
	pthread_mutex_unlock(philo[i].lfork);
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
		//	pthread_mutex_unlock(philo[i].print);
			ft_print_actions(master, philo, i, "died\n");
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

int	ft_philo_sleep(t_master *master, t_philo *philo, int i)
{
	ft_print_actions(master, philo, i, "is sleeping\n");
//	printf("            [%d]\n", master->tsleep);
	if (waiting(master, (int)getstart_time(), master->tsleep))
		return (1);
	return (0);
}

void	ft_philo_thinking(t_master *master, t_philo *philo, int i)
{
	ft_print_actions(master, philo , i, "is thinking\n");
//	usleep(master->tthink);
}

int	ft_parsing_actions(t_master *master, t_philo *philo, int i)
{
	/*if (ft_you_are_dead(master, philo))
	{
		master->end = 1;
		return (1);
	}*/
	//if (master->phmaxeat >= master->nbphilo)
	//	return (1);
	if (ft_philo_fight_foreat(master, philo, i))
		return (1);
	//if (master->end == 1)
	//	return (1);
	if (ft_philo_sleep(master, philo , i))
		return (1);
	//faire une fonction stop sleep , usleep?
	ft_philo_thinking(master, philo, i);	
	if (master->maxeat != -1 && philo[i].nbr_meal >= master->maxeat)
		return (1);
	//if (master->end == 1)
	//	return (1);
	return (0);
}
