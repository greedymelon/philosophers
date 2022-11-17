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
		pthread_mutex_unlock(infos->dying);
		if (infos->time_to_die <= time_msec() - times->start - times->last_eat)
		{
			print_action(infos, DYING, times);
			return (DEAD);
		}
	}
	return (ALIVE);
}

int	dead_or_print(t_info *infos, int action, t_time *times)
{
	long int	time;

	pthread_mutex_lock(infos->dying);
	if (infos->schr_box == DEAD)
	{
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->dying);
	time = time_msec() - times->start;
	if (infos->time_to_die > time - times->last_eat)
	{	
		print_action(infos, action, times);
		if (action == EAT)
			times->last_eat = time;
	}
	else
	{
		print_action(infos, DYING, times);
		return (DEAD);
	}
	return (ALIVE);
}

// int	fork_or_die(t_info *infos, t_time *times)
// {
// 	if (dead_or_print(infos, FORK, times) == DEAD)
// 		return (DEAD);
// 	return (ALIVE);
// }

int	eat_or_die(t_info *infos, t_time *times)
{
	int n_eat;

	if (dead_or_print(infos, EAT, times) == DEAD)
		return (DEAD);
	if (sleep_act(times, infos->time_to_eat, infos) == DEAD)
		return (DEAD);
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	n_eat = infos->n_times_eat;
	pthread_mutex_unlock(infos->dying);
	if (n_eat == 0)
		return (DEAD);
	return (ALIVE);
}

//int	sleep_or_die(t_info *infos, t_time *times)
// {
// 	if (dead_or_print(infos, SLEEP, times) == DEAD)
// 		return (DEAD);
// 	if(sleep_act(times, infos->time_to_sleep, infos) == DEAD)
// 		return (DEAD);
// 	return (ALIVE);
// }
