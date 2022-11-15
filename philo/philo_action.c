#include "philo.h"

int	dead_or_print(t_info *infos, int action, int times)
{
	pthread_mutex_lock(infos->write);
	if (print_action(infos, action, times))
	{	
		pthread_mutex_unlock(infos->write);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->write);
	return (ALIVE);
}

int	fork_or_die(t_info *infos, t_time *times)
{
	long int	fork_time;

	fork_time = time_msec();
	if (infos->time_to_die >= fork_time - times->last_eat)
	{	
		if (dead_or_print(infos, FORK, fork_time))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		infos->schr_box = DEAD;
		pthread_mutex_lock(infos->dying);
		print_dead(times->last_eat + infos->time_to_die, infos);
		return (DEAD);
	}
	return (ALIVE);
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
		pthread_mutex_lock(infos->dying);
		infos->schr_box = DEAD;
		pthread_mutex_lock(infos->dying);
		print_dead(times->last_eat + infos->time_to_die, infos);
		return (DEAD);
	}
	infos->n_times_eat--;
	if (!infos->n_times_eat)
	{	
		pthread_mutex_lock(infos->dying);
		infos->schr_box = DEAD;
		pthread_mutex_lock(infos->dying);
		return (DEAD);
	}
	usleep(infos->time_to_eat);
	return (ALIVE);
}

int	sleep_or_die(t_info *infos, t_time *times)
{
	long int	sleep_time;

	sleep_time = time_msec();
	if (infos->time_to_die >= sleep_time - times->last_eat)
	{	
		if (dead_or_print(infos, SLEEP, times->corr_eat))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		infos->schr_box = DEAD;
		pthread_mutex_lock(infos->dying);
		print_dead(times->last_eat + infos->time_to_die, infos);
		return (DEAD);
	}
	usleep(infos->time_to_sleep);
	return (ALIVE);
}

int	think_or_die(t_info *infos, t_time *times)
{
	long int	think_time;

	think_time = time_msec();
	times->corr_eat = time_msec();
	if (infos->time_to_die >= think_time - times->last_eat)
	{	
		if (dead_or_print(infos, THINK, think_time))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		infos->schr_box = DEAD;
		pthread_mutex_lock(infos->dying);
		print_dead(times->last_eat + infos->time_to_die, infos);
		return (DEAD);
	}
	return (ALIVE);
}