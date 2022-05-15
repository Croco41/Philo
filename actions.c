/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 16:03:01 by cgranja          ###   ########.fr       */
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
	philo[i].last_meal = get_time();
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat;)
	{
		master->phmaxeat++;
	}
	pthread_mutex_unlock(philo[i].mutex_lfork);
	pthread_mutex_unlock(philo[i].mutex_rfork);
	return (0);
}	

int ft_philo_sleep(t_master *master, t_philo *philo, int i)
{

}

int ft_parsing_actions(t_master *master, t_philo *philo, int i)
{

}

