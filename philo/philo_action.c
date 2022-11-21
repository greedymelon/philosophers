/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:03:14 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_bool	sleep_act(t_time *times, long int time, t_info *infos)
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

void	*unlock_fork(t_info *infos, int fork_fir, int fork_sec)
{
	pthread_mutex_unlock(&(infos->fork)[fork_fir]);
	pthread_mutex_unlock(&(infos->fork)[fork_sec]);
	return (NULL);
}

t_bool	dead_or_print(t_info *infos, int action, t_time *times)
{
	pthread_mutex_lock(infos->dying);
	if (infos->schr_box == DEAD)
	{
		pthread_mutex_unlock(infos->dying);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->dying);
	if (infos->time_to_die > time_msec() - times->start - times->last_eat)
		return (print_action(infos, action, times));
	else
	{
		print_action(infos, DYING, times);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	fork_or_die(t_info *infos, t_time *times, int fork_fir, int fork_sec)
{
	pthread_mutex_lock(&(infos->fork)[fork_fir]);
	if (dead_or_print(infos, FORK, times) == DEAD)
	{
		pthread_mutex_unlock(&(infos->fork)[fork_fir]);
		return (DEAD);
	}
	pthread_mutex_lock(&(infos->fork)[fork_sec]);
	if (dead_or_print(infos, FORK, times) == DEAD)
	{
		unlock_fork(infos, fork_fir, fork_sec);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	eat_or_die(t_info *infos, t_time *times)
{
	int	n_eat;

	if (dead_or_print(infos, EAT, times) == DEAD)
		return (DEAD);
	times->last_eat = time_msec() - times->start;
	if (sleep_act(times, infos->time_to_eat, infos) == DEAD)
		return (DEAD);
	times->last_eat = time_msec() - times->start;
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	n_eat = infos->n_times_eat;
	pthread_mutex_unlock(infos->dying);
	if (n_eat == 0)
		return (DEAD);
	return (ALIVE);
}
