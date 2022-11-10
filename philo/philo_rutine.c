#include "philo.h"

int	tv_msec(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

int	time_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv_msec(&tv))
}

int	dead_or_print(t_info *infos, int action, int times)
{
	pthread_mutex_lock(infos->write_die);
	if (infos->dead == YES)
	{
		pthread_mutex_unlock(infos->write_die);
		return (YES);
	}
	print_action(infos->philo_id, action, times);
	pthread_mutex_unlock(infos->write_die);
}

int	eat_or_die(t_info *infos, t_time *times)
{
	times->corr_eat = time_msec();
	if (infos->time_to_die >= times->corr_eat - times->last_eat)
	{	
		if (dead_or_print(infos, EAT, times->corr_eat))
			return (DEAD);
		times->last_eat = times->corr_eat;
	}
	else
	{
		pthread_mutex_lock(infos->write_die);
		infos->dead = YES;
		pthread_mutex_lock(infos->write_die);
		return (DEAD)
	}
	infos->n_times_eat--;
	if (!infos->n_times_eat)
	{	
		pthread_mutex_lock(infos->write_die);
		infos->dead = YES;
		pthread_mutex_lock(infos->write_die);
		return (DEAD);
	}
	usleep(infos->time_to_eat);
	return (ALIVE)
}
void	routine_even(void *info)
{
	t_info	*infos;
	int		next_philo;
	t_time	times;

	infos = info;
	next_philo = calc_next(infos);
	while (*(infos->start) == NO);
	times.start = time_msec();
	times.last_eat = 0;
	while (!infos->dead)
	{
		pthread_mutex_lock(infos->fork[infos->philo_id - 1]);
		if (fork_or_die(infos, &times) ==  DEAD)
			return (NULL);
		pthread_mutex_lock(infos->fork[next_philo]);
		if (eat_or_die(infos, &times) ==  DEAD)
			return (NULL);
		pthread_mutex_unlock(infos->fork[next_philo]);
		pthread_mutex_unlock(infos->fork[infos->philo_id - 1]);
		if (sleep_or_die(infos, &times) ==  DEAD)
			return (NULL);
		if (think_or_die(infos, &times) ==  DEAD)
			return (NULL);
	}
	return (NULL);
}

void	routine_odd(void *info)