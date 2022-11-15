#include "philo.h"


int	sleep_act(t_time *times, long int time, t_info *infos)
{
	long int	start;

	start = time_msec();
	while (time > time_msec() - start)
	{
		usleep(50);
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		
		if (infos->time_to_die <= time_msec() - times->last_eat)
		{
			infos->schr_box = DEAD;
			print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		pthread_mutex_unlock(infos->dying);
	}
	return (ALIVE);
}

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
		if (dead_or_print(infos, FORK, fork_time - times->start))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		infos->schr_box = DEAD;
		print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	return (ALIVE);
}

int	eat_or_die(t_info *infos, t_time *times)
{
	times->corr_eat = time_msec();
	if (infos->time_to_die >= times->corr_eat - times->last_eat)
	{	
		if (dead_or_print(infos, EAT, times->corr_eat - times->start))
			return (DEAD);
		times->last_eat = times->corr_eat;
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		infos->schr_box = DEAD;
		print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	pthread_mutex_unlock(infos->dying);
	if (!infos->n_times_eat)
	{	
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	if (sleep_act(times, infos->time_to_eat, infos) == DEAD)
		return (DEAD);
	return (ALIVE);
}

int	sleep_or_die(t_info *infos, t_time *times)
{
	long int	sleep_time;

	sleep_time = time_msec();
	if (infos->time_to_die >= sleep_time - times->last_eat)
	{	
		if (dead_or_print(infos, SLEEP, sleep_time - times->start))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		infos->schr_box = DEAD;
		print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	if(sleep_act(times, infos->time_to_sleep, infos) == DEAD)
		return (DEAD);
	return (ALIVE);
}

int	think_or_die(t_info *infos, t_time *times)
{
	long int	think_time;

	think_time = time_msec();
	times->corr_eat = time_msec();
	if (infos->time_to_die >= think_time - times->last_eat)
	{	
		if (dead_or_print(infos, THINK, think_time - times->start))
			return (DEAD);
	}
	else
	{
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		infos->schr_box = DEAD;
		print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	return (ALIVE);
}