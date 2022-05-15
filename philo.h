/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:42:55 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 02:10:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/times.h>
# include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_philo
{
	pthread_t	philo;
	pthread_mutex_t fork;
	pthread_mutex_t print;
	size_t		last_meal;
	int		nbr_meal;
	int		id;
}		t_philo;

typedef struct s_master
{
	t_philo		*philo;
	int		nbphilo;
	int		dead;
	int		tdie;
	int		teat;
	int		tsleep;
	int		maxeat;
	size_t		start_time;

}		t_master;









#endif
