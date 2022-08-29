#include "philo.h"

void	init_info(t_info *info, char **argv)
{
	info->n_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->n_times_eat = ft_atoi(argv[5]);
}

void	thread_init(t_info *info)
{
	int	i;

	i = 1;
	while (i < info->n_philo)
	{
		if(!pthread_create(&(info->philo)[i], NULL, &routine, info, i))
			exit (1);
		i++;
	}
}