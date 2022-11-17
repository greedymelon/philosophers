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
			pthread_mutex_unlock(infos->dying);
			print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
			return (DEAD);
		}
		pthread_mutex_unlock(infos->dying);
	}
	return (ALIVE);
}

int	dead_or_print(t_info *infos, int action, t_time *times)
{
	long int action_time;


	pthread_mutex_lock(infos->write);
	action_time = time_msec();
	if (infos->time_to_die >= action - times->last_eat)
	{	
		if (print_action(infos, action, action_time - times->start))
		{	
			pthread_mutex_unlock(infos->write);
			return (DEAD);
		}
		else if (action == EAT)
			times->last_eat = action_time;
	}
	else
	{
		pthread_mutex_unlock(infos->write);
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		pthread_mutex_unlock(infos->dying);
		print_dead(times->start, times->last_eat - times->start + infos->time_to_die, infos);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->write);
	return (ALIVE);
}

int	fork_or_die(t_info *infos, t_time *times)
{
	if (dead_or_print(infos, FORK, times))
			return (DEAD);
	return (ALIVE);
}

int	eat_or_die(t_info *infos, t_time *times)
{
	int n_eat;

	if (dead_or_print(infos, EAT, times))
		return (DEAD);
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	n_eat = infos->n_times_eat;
	pthread_mutex_unlock(infos->dying);
	if (!n_eat)
		return (DEAD);
	if (sleep_act(times, infos->time_to_eat, infos) == DEAD)
		return (DEAD);
	return (ALIVE);
}

int	sleep_or_die(t_info *infos, t_time *times)
{
	if (dead_or_print(infos, SLEEP, times))
		return (DEAD);
	if(sleep_act(times, infos->time_to_sleep, infos) == DEAD)
		return (DEAD);
	return (ALIVE);
}

int	think_or_die(t_info *infos, t_time *times)
{
	if (dead_or_print(infos, THINK, times))
		return (DEAD);
	return (ALIVE);
}