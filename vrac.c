id	taken_a_fork(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&philo->fork);
	print(philo, "has taken a fork");
	if (read_int(&rules->mutex_rules, &rules->nbr) == 1)
	{
		while (read_int(&rules->mutex_sig, &rules->sig) != SIG_TERMINATE)
			usleep(100);
		return ;
	}
	pthread_mutex_lock(&philo->previous->fork);
	print(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&philo->mutex_is_eating);
	print(philo, "is eating");
	write_llu(&philo->mutex_philo, &philo->last_eat,
		gettime(read_llu(&philo->mutex_philo, &philo->time_zero)));
	write_int(&philo->mutex_philo, &philo->nbr_eat, philo->nbr_eat + 1);
	write_int(&rules->mutex_oec, &rules->odd_even_count,
		read_int(&rules->mutex_oec, &rules->odd_even_count) + 1);
	my_usleep(read_llu(&rules->mutex_rules, &rules->eat), philo);
	pthread_mutex_unlock(&philo->mutex_is_eating);
	pthread_mutex_unlock(&philo->previous->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	sleeping(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	print(philo, "is sleeping");
	my_usleep(read_llu(&rules->mutex_rules, &rules->sleep), philo);
}

void	thinking(t_philo *philo)
{
	print(philo, "is thinking");
}

void	actions(t_philo *philo)
{
	if (read_int(&philo->mutex_philo, &philo->state) == IS_FULL)
		return ;
	taken_a_fork(philo);
	if (read_int(&philo->mutex_philo, &philo->state) == IS_FULL)
		return ;
	eating(philo);
	if (read_int(&philo->mutex_philo, &philo->state) == IS_FULL)
		return ;
	sleeping(philo);
	if (read_int(&philo->mutex_philo, &philo->state) == IS_FULL)
		return ;
	thinking(philo);

}

#include "philo.h"

int	assign_forks(t_board *board, t_philo *philo, int id)
{
	if (!id)
	{
		philo[id].l_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		philo[id].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[id].l_fork || pthread_mutex_init(philo[id].l_fork, NULL)
			|| !philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	else if (id == board->number - 1)
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = philo[0].l_fork;
	}
	else
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	return (0);
}

void	init_color(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	ft_strcpy(board->color[0], DEF);
	ft_strcpy(board->color[1], YELLOW);
	ft_strcpy(board->color[2], GREEN);
	ft_strcpy(board->color[3], RED);
	ft_strcpy(board->color[4], BLUE);
	ft_strcpy(board->color[5], PURPLE);
	ft_strcpy(board->color[6], CYAN);
	while (++i < board->number)
		ft_strcpy(philo[i].color, board->color[i % 7]);
}

int	init_philo(t_board *board, t_philo *philo)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*lock;
	int				i;

	i = -1;
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!print || pthread_mutex_init(print, NULL))
		return (1);
	lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!lock || pthread_mutex_init(lock, NULL))
		return (1);
	init_color(board, philo);
	while (++i < board->number)
	{
		philo[i].count_meal = 0;
		philo[i].print = print;
		if (assign_forks(board, philo, i))
			return (1);
	}
	board->lock = lock;
	return (0);
}

int	start_philo(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	board->id = 0;
	board->rip = -1;
	board->full_number = 0;
	board->stop = 0;
	board->philo = philo;
	board->start_time = get_time();
	while (++i < board->number)
	{
		philo[i].last_meal = get_time();
		if (pthread_create(&(philo[i].philo), NULL, &routine, board))
			return (1);
	}
	while (!check_death(board, philo))
		usleep(DELAY);
	i = -1;
	while (++i < board->number)
		pthread_join(philo[i].philo, NULL);
	return (0);
}

void	free_philo(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	free(philo[0].print);
	free(board->lock);
	while (++i < board->number)
	{
		philo[0].print = NULL;
		if (!i)
		{
			free(philo[i].l_fork);
			free(philo[i].r_fork);
		}
		else if (i != board->number - 1)
			free(philo[i].r_fork);
	}
	free(philo);
	free(board);
	philo = NULL;
	board = NULL;
}











#include "philo.h"

void	philo_speak(t_board *board, t_philo *philo, char *str, int id)
{
	pthread_mutex_lock(philo[id].print);
	pthread_mutex_lock(board->lock);
	if (!board->stop)
	{
		ft_putstr(philo[id].color);
		ft_putnbr(get_time() - board->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)id + 1);
		write(1, " ", 1);
		ft_putstr(str);
		ft_putstr("\033[0m");
	}
	if (board->rip == id)
		board->stop = 1;
	pthread_mutex_unlock(board->lock);
	pthread_mutex_unlock(philo[id].print);
}

int	usleep_custom(t_board *board, size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(board->lock);
		if (board->stop)
			return (pthread_mutex_unlock(board->lock) + 1);
		pthread_mutex_unlock(board->lock);
		usleep(DELAY);
	}
	return (0);
}

int	philo_eat(t_board *board, t_philo *philo, int id)
{
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].r_fork);
	philo_speak(board, philo, "has taken a fork\n", id);
	if (board->number != 1)
		philo_speak(board, philo, "has taken a fork\n", id);
	else
		usleep_custom(board, board->die + 1);
	philo_speak(board, philo, "is eating\n", id);
	pthread_mutex_lock(board->lock);
	philo[id].last_meal = get_time();
	philo[id].count_meal++;
	if (philo[id].count_meal >= board->limit)
		board->full_number++;
	pthread_mutex_unlock(board->lock);
	if (usleep_custom(board, board->eat))
	{
		pthread_mutex_unlock(philo[id].l_fork);
		pthread_mutex_unlock(philo[id].r_fork);
		return (1);
	}
	pthread_mutex_unlock(philo[id].l_fork);
	pthread_mutex_unlock(philo[id].r_fork);
	return (0);
}

int	check_death(t_board *board, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < board->number)
	{
		pthread_mutex_lock(board->lock);
		if (board->stop)
			return (pthread_mutex_unlock(board->lock) + 1);
		if (get_time() - philo[i].last_meal >= (size_t)board->die)
		{
			board->rip = i;
			pthread_mutex_unlock(philo[i].print);
			pthread_mutex_unlock(board->lock);
			philo_speak(board, philo, "died\n", i);
			return (1);
		}
		if (board->limit != -1 && board->full_number == board->number)
		{
			board->stop = 1;
			return (pthread_mutex_unlock(board->lock) + 1);
		}
		pthread_mutex_unlock(board->lock);
	}
	return (0);
}

int	philo_live(t_board *board, t_philo *philo, int id)
{
	if (philo_eat(board, philo, id))
		return (1);
	philo_speak(board, philo, "is sleeping\n", id);
	if (usleep_custom(board, board->sleep))
		return (1);
	philo_speak(board, philo, "is thinking\n", id);
	if (board->limit != -1 && philo[id].count_meal >= board->limit)
		return (1);
	return (0);
}

