/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:12:25 by user42            #+#    #+#             */
/*   Updated: 2022/05/13 19:43:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	getstart_time(void)
{
	struct timeval	current;
	size_t	time;

	if (gettimeofday(&current, NULL) != 0)
		return (1);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);

}

void	*routine(void *arg)
{
	t_master	*master,
	t_philo		*philo;

	master = (t_master *)arg;

}
