/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 15:24:17 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_bool	sleep_act(t_info *info, long int start, long int time)
{
	long int	corr_time;

	while (time > time_msec() - (start + info->start))
	{
		usleep(250);
		corr_time = time_msec() - info->start;
		if (info->time_to_die <= corr_time - info->last_eat)
			return (print_action(info, corr_time, DYING));
	}
	return (ALIVE);
}

static t_bool	st_take_or_die(t_info *info, int fork_n)
{
	int	taken;
	int	corr_time;

	taken = 0;
	while (!taken)
	{
		corr_time = time_msec() - info->start;
		if (info->time_to_die <= corr_time - info->last_eat)
			return (print_action(info, corr_time, DYING));
		pthread_mutex_lock(info->dying);
		if (info->fork_lock[fork_n] == AVAILABLE)
		{	
			info->fork_lock[fork_n] = UNAVAILABLE;
			pthread_mutex_unlock(info->dying);
			break ;
		}
		pthread_mutex_unlock(info->dying);
		usleep(250);
	}
	return (ALIVE);
}

t_bool	fork_or_die(t_info *infos, int fork_fir, int fork_sec)
{
	long int	time;

	if (st_take_or_die(infos, fork_fir) == DEAD)
		return (DEAD);
	pthread_mutex_lock(&(infos->fork)[fork_fir]);
	time = time_msec() - infos->start;
	if (print_or_die(infos, time, FORK) == DEAD
		|| st_take_or_die(infos, fork_sec) == DEAD)
	{
		set_fork_status(infos, fork_fir, NONE_F, AVAILABLE);
		pthread_mutex_unlock(&(infos->fork)[fork_fir]);
		return (DEAD);
	}
	pthread_mutex_lock(&(infos->fork)[fork_sec]);
	time = time_msec() - infos->start;
	if (print_or_die(infos, time, FORK) == DEAD)
	{
		unlock_fork(infos, fork_sec, fork_fir);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	eat_or_die(t_info *info, int *meal_n)
{
	long int	time;

	time = time_msec() - info->start;
	if (print_or_die(info, time, EAT) == DEAD)
		return (DEAD);
	info->last_eat = time;
	if (sleep_act(info, time, info->time_to_eat) == DEAD)
		return (DEAD);
	*meal_n -= 1;
	if (*meal_n == 0)
	{
		pthread_mutex_lock(info->dying);
		info->n_times_eat = 0;
		pthread_mutex_unlock(info->dying);
		return (DEAD);
	}	
	return (ALIVE);
}

t_bool	sleep_or_die(t_info *info)
{
	long int	time;

	time = time_msec() - info->start;
	if (print_or_die(info, time, SLEEP) == DEAD)
		return (DEAD);
	if (sleep_act(info, time, info->time_to_sleep) == DEAD)
		return (DEAD);
	return (ALIVE);
}
