/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:50:00 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 15:36:43 by cgranja          ###   ########.fr       */
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
printf("nbphilo: %d\n", master->nbphilo);
printf("nbmeal: %d\n", philo[i].nbr_meal);
	pthread_mutex_lock(philo[i].lfork);
	pthread_mutex_lock(philo[i].rfork);
	if (master->nbphilo > 1)
	{
		ft_print_actions(master, philo, i, "has taken a fork\n");
	}
	ft_print_actions(master, philo, i, "has taken a fork\n");
	if (master->nbphilo == 1)
	{
		printf("tdie %d\n", master->tdie);

		while ((int)getstart_time() - (int)master->start_time < master->tdie)
		{
			printf("%zu & %d\n", getstart_time(), master->tdie);
			usleep(100);
		}

		printf("hdi");

//		usleep(master->tdie * 1000 - (getstart_time() *1000) -master->start_time);
		master->end = 1;
		ft_print_actions(master, philo, i, "died\n");
		return(1);
	}
	ft_print_actions(master, philo, i, "is eating\n");
	philo[i].last_meal = getstart_time();

printf("nblastmeal: %zu\n", philo[i].last_meal);
	philo[i].nbr_meal++;
	if (philo[i].nbr_meal == master->maxeat)
	{
		master->phmaxeat++;
	}
	//fonctio usleep?
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
	if (ft_you_are_dead(master, philo) == 1)
	{
		master->end = 1;
		return (1);
	}
	//if (master->phmaxeat >= master->nbphilo)
	//	return (1);
	if (ft_philo_fight_foreat(master, philo, i) == 1)
		return (1);
	ft_philo_sleep(master, philo , i);
	//faire une fonction stop sleep , usleep?
	ft_philo_thinking(master, philo, i);	
	if (master->maxeat != -1 && master->phmaxeat >= master->nbphilo)
		return (1);
	return (0);
}
