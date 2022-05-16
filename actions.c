/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 02:15:29 by user42           ###   ########.fr       */
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
	if (master->end < 0)
	{
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
	pthread_mutex_lock(philo[i].mutex_lfork);
	pthread_mutex_lock(philo[i].mutex_rfork);
	if (master->nbphilo > 1)
	{
		ft_print_actions(master, philo, i, "has taken a fork\n");
	}
	ft_print_actions(master, philo, i, "has taken a fork\n");
	ft_print_actions(master, philo, i, "is eating\n");
	philo[i].last_meal = getstart_time();
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat)
	{
		master->phmaxeat++;
	}
	//fonctio usleep?
	pthread_mutex_unlock(philo[i].mutex_lfork);
	pthread_mutex_unlock(philo[i].mutex_rfork);
	return (0);
}	

int	ft_you_are_dead(t_master *master, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < master->nbphilo)
	{
		if (getstart_time() - philo[i].last_meal > (size_t)master->tdie)
		{
			master->dead = 1;
			pthread_mutex_unlock(philo[i].print);
			ft_print_actions(master, philo, i, "died\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_philo_sleep(t_master *master, t_philo *philo, int i)
{
	ft_print_actions(master, philo, i, "is sleeping\n");
}

void	ft_philo_thinking(t_master *master, t_philo *philo, int i)
{
	ft_print_actions(master, philo , i, "is thinking\n");
}

int	ft_parsing_actions(t_master *master, t_philo *philo, int i)
{
	if (master->phmaxeat >= master->nbphilo)
		return (1);
	if (ft_philo_fight_foreat(master, philo, i) == 1)
		return (1);
	ft_philo_sleep(master, philo , i);
	//faire une fonction stop sleep , usleep?
	ft_philo_thinking(master, philo, i);
	return (0);
}
