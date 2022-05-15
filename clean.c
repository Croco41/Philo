/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:27:31 by user42            #+#    #+#             */
/*   Updated: 2022/05/14 17:32:06 by user42           ###   ########.fr       */
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

int ft_free_philo(t_master *master, t_philo *philo)
{

}


int ft_destroy_all(t_master *master, t_philo *philo)
{

}
