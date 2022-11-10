#include "philo.h"


void	init_thread(t_info **info)
{
	int	i;

	i = 1;
	while (i < info[0]->n_philo)
	{
		if (info[i]->philo_id % 2 == 0)
			if(!pthread_create(info[i]->philo, NULL, &routine_even, info[i]))
				exit (1);
		else
			if(!pthread_create(info[i]->philo, NULL, &routine_odd, info[i]))
				exit (1);
		i++;
	}
}

pthread_mutex_t	**forks_init(pthread_mutex_t **forks, int n_philo)
{
	int	i;

	i = 0;
	while(i < n_philo)
	{
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

void	init_info(t_info **info, char **argv, pthread_mutex_t *write_die,
		pthread_mutex_t **forks )
{
	int				i;
	int				n_philo;

	i = 0;
	n_philo = ft_atoi(argv[1]);
	forks_init(forks, n_philo);
	pthread_mutex_init(write_die, NULL);
	while (i < n_philo)
	{
		info[i]->n_philo = n_philo;
		info[i]->time_to_die = ft_atoi(argv[2]);
		info[i]->time_to_eat = ft_atoi(argv[3]) * 1000;
		info[i]->time_to_sleep = ft_atoi(argv[4]) * 1000;
		info[i]->n_times_eat = ft_atoi(argv[5]);
		info[i]->dead = NO;
		info[i]->philo_id = i + 1;
		info[i]->fork = forks;
		info[i]->write_die = write_die;
	}
}

