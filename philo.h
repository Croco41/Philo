/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:42:55 by user42            #+#    #+#             */
/*   Updated: 2022/05/16 14:27:14 by cgranja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/time.h>
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
	pthread_mutex_t			*lfork;
	pthread_mutex_t			*rfork;
	pthread_mutex_t			*print;
	size_t		last_meal;
	int			nbr_meal;
//	int		iofp;
}		t_philo;

typedef struct s_master
{
	t_philo		*philo;
	int			iofp;
	int			nbphilo;
	int			dead;
	int			tdie;
	int			teat;
	int			tsleep;
	int			maxeat;
	size_t		start_time;
	int			end; //ini dansstart philo mais m'en sers pas?
	int			phmaxeat;

}		t_master;

/*
 * *************************UTILS*************************
 */

int		ft_atoi(char *str);
void	ft_putnbr(size_t n);
void	ft_putstr(char *str);

/*
 *  ****************************MAIN************************
 */

int		main(int ac, char **av);
char	*parsing(int ac, char **av, t_master *master);
int		ft_create_threads(t_master *master, t_philo *philo);
int		ft_init_philo(t_master *master, t_philo *philo);

/*
 * ***************************PHILO**************************
 */

int		ft_start_philo(t_master *master, t_philo *philo);
int		link_philo_forks(int i, t_master *master, t_philo *philo);

/*
 * *******************************ROUTINE**********************
 */

size_t	getstart_time(void);
void	*routine(void *arg);

/*
 * *************************************ACTIONS***************
 */

int		ft_parsing_actions(t_master *master, t_philo *philo, int i);
int		ft_you_are_dead(t_master *master, t_philo *philo);
void	ft_philo_sleep(t_master *master, t_philo *philo, int i);
void	ft_philo_thinking(t_master *master, t_philo *philo, int i);
int		ft_philo_fight_foreat(t_master *master, t_philo *philo, int i);
void	ft_print_actions(t_master *master, t_philo *philo, int i, char *str);

/*
 * ****************************CLEAN**************************
 */

int		ft_quit_free(t_master *master, t_philo *philo);
int		ft_destroy_all(t_master *master, t_philo *philo);

#endif
