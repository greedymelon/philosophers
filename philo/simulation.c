#include "philo.h"

static void	create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info[0].n_philo)
	{
		if (info[i].philo_id % 2 == 0)
			pthread_create(&(info[i]).philo, NULL, &routine_even, &info[i]);
		else
			pthread_create(&(info[i]).philo, NULL, &routine_odd, &info[i]);
		i++;
	}
}
void	philo_join(t_info *infos)
{
	int	i;

	i = 0;
	while (i < infos[0].n_philo)
	{
		pthread_join(infos[i].philo, NULL);
		i++;
	}
}
void	set_dead(t_info *infos)
{
	int	i;

	i = 0;
	while (i < infos[0].n_philo)
	{
		infos[i].schr_box = DEAD;
		i++;
	}
}
void	*monitoring(void *info)
{
	int	i;
	t_info	*infos;
	int	all_eat;

	infos = info;
	i = 0;
	while ( 1 )
	{
		all_eat = 0;
		pthread_mutex_lock(infos[0].dying);
		while (i < infos[0].n_philo)
		{
			if (infos[i].schr_box == DEAD)
			{	
				set_dead(infos);
				pthread_mutex_unlock(infos[0].dying);
				return (NULL);
			}
			if (infos[i].n_times_eat == 0)
				all_eat++;
			i++;
		}
		pthread_mutex_unlock(infos[0].dying);
		if (all_eat == infos[0].n_philo)
			return (NULL);
		i = 0;
	}
	return (NULL);
}

void	start_simulation(t_info *info)
{
	pthread_t	monitor;

	if(pthread_create(&monitor, NULL, &monitoring, info))
		return ;
	create_thread(info);
	pthread_join(monitor, NULL);
	philo_join(info);
}