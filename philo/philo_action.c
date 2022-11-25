/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 13:22:08 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_bool	sleep_act(t_info *infos, long int start, long int eat, long int time)
{
	long int	corr_time;

	while (time > time_msec() - (start + infos->start))
	{
		usleep(250);
		corr_time = time_msec() - infos->start;
		if (infos->time_to_die <= corr_time - eat)
			return (print_action(infos, corr_time, eat, DYING));
	}
	return (ALIVE);
}

t_bool	print_or_die(t_info *infos, long int time, long int eat, int action)
{
	if (infos->time_to_die > time - eat)
		return (print_action(infos, time, eat, action));
	else
		return (print_action(infos, time, eat, DYING));
	return (ALIVE);
}

t_bool	fork_or_die(t_info *infos, long int eat, int fork_fir, int fork_sec)
{
	long int	time;

	pthread_mutex_lock(&(infos->fork)[fork_fir]);
	time = time_msec() - infos->start;
	if (print_or_die(infos, time, eat, FORK) == DEAD)
	{
		pthread_mutex_unlock(&(infos->fork)[fork_fir]);
		return (DEAD);
	}
	pthread_mutex_lock(&(infos->fork)[fork_sec]);
	time = time_msec() - infos->start;
	if (print_or_die(infos, time, eat, FORK) == DEAD)
	{
		unlock_fork(infos, fork_sec, fork_fir);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	eat_or_die(t_info *infos, long int *eat)
{
	int			n_eat;
	long int	time;

	time = time_msec() - infos->start;
	if (print_or_die(infos, time, *eat, EAT) == DEAD)
		return (DEAD);
	*eat = time;
	if (sleep_act(infos, time, time, infos->time_to_eat) == DEAD)
		return (DEAD);
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	n_eat = infos->n_times_eat;
	pthread_mutex_unlock(infos->dying);
	if (n_eat == 0)
		return (DEAD);
	return (ALIVE);
}

t_bool	sleep_or_die(t_info *infos, long int eat)
{
	long int	time;

	time = time_msec() - infos->start;
	if (print_or_die(infos, time, eat, SLEEP) == DEAD)
		return (DEAD);
	if (sleep_act(infos, time, eat, infos->time_to_sleep) == DEAD)
		return (DEAD);
	return (ALIVE);
}
