/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 18:12:52 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// manger
// prendre une fourchette
// dormir
// penser
// truc global actions
//
void	ft_print_actions(t_master *master, t_philo *philo, int i, char *str)
{
	pthread_mutex_lock(philo[i].print);
	if (master->end == 0)
	{
	ft_putnbr(getstart_time() - master->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)i + 1);
		write(1, " ", 1);
		ft_putstr(str);
	}	
	if (master->dead > 0 || master->end ==1) 
	{
		master->end = 1;
		ft_putnbr(getstart_time() - master->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)i + 1);
		write(1, " ", 1);
		ft_putstr(str);
	}
	pthread_mutex_unlock(philo[i].print);
}

int	ft_philo_fight_foreat(t_master *master, t_philo *philo, int i)
{
//printf("nbphilo: %d\n", master->nbphilo);
//printf("nbmeal: %d\n", philo[i].nbr_meal);
	pthread_mutex_lock(philo[i].lfork);
	pthread_mutex_lock(philo[i].rfork);
	if (master->nbphilo > 1)
	{
		ft_print_actions(master, philo, i, "has taken a fork\n");
	}
	ft_print_actions(master, philo, i, "has taken a fork\n");
	if (master->nbphilo == 1)
	{
		while ((int)getstart_time() - (int)master->start_time < master->tdie)
			usleep(100);
		master->end = 1;
		ft_print_actions(master, philo, i, "died\n");
		return (1);
	}
	ft_print_actions(master, philo, i, "is eating\n");
	pthread_mutex_lock(master->locktime);
	philo[i].last_meal = getstart_time();
	pthread_mutex_unlock(master->locktime);
//printf("nblastmeal: %zu\n", philo[i].last_meal);
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat)
	{
		master->phmaxeat++;
	}
//	printf("--------------[%d]\n", master->teat);
	if (waiting(master, master->start_time, master->teat))
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
			master->end = 1;
			pthread_mutex_unlock(master->locktime);
		//	pthread_mutex_unlock(philo[i].print);
			ft_print_actions(master, philo, i, "died\n");
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
	if (waiting(master, master->start_time, master->tsleep))
		return (1);
	return (0);
}

void	ft_philo_thinking(t_master *master, t_philo *philo, int i)
{
	ft_print_actions(master, philo , i, "is thinking\n");
}

int	ft_parsing_actions(t_master *master, t_philo *philo, int i)
{
	/*if (ft_you_are_dead(master, philo) == 1)
	{
		master->end = 1;
		return (1);
	}*/
	//if (master->phmaxeat >= master->nbphilo)
	//	return (1);
	if (ft_philo_fight_foreat(master, philo, i) == 1)
		return (1);
	if (master->end == 1)
		return (1);
	if (ft_philo_sleep(master, philo , i))
		return (1);
	//faire une fonction stop sleep , usleep?
	ft_philo_thinking(master, philo, i);	
	if (master->maxeat != -1 && master->phmaxeat >= master->nbphilo)
		return (1);
	if (master->end == 1)
		return (1);
	return (0);
}
