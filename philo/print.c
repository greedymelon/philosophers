/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:12 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 15:22:58 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static t_bool	st_unlock_threads(t_info *info)
{
	pthread_mutex_unlock(info->dying);
	pthread_mutex_unlock(info->write);
	return (DEAD);
}

static t_bool	st_print_error(t_info *info)
{
	pthread_mutex_lock(info->dying);
	if (info->schr_box == DEAD)
		return (st_unlock_threads(info));
	info->schr_box = DEAD;
	pthread_mutex_unlock(info->dying);
	write(2, "ERROR TIME\n", 11);
	ft_wait_ms(info->time_to_die * 2);
	pthread_mutex_unlock(info->write);
	return (DEAD);
}

static void	st_print(t_info *info, long int time, int act_n)
{
	const char	action[5][18] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	printf("%ld %d %s\n", time, info->philo_id,
		action[act_n]);
}

t_bool	print_action(t_info *info, long int time, int act_n)
{
	pthread_mutex_lock(info->write);
	if (act_n == DYING && (time_msec() - info->start) - info->last_eat
		> info->time_to_die + 10)
		return (st_print_error(info));
	pthread_mutex_lock(info->dying);
	if (info->schr_box == DEAD)
		return (st_unlock_threads(info));
	st_print(info, time, act_n);
	if (act_n == DYING)
	{	
		info->schr_box = DEAD;
		pthread_mutex_unlock(info->dying);
		ft_wait_ms(info->time_to_die * 2);
		pthread_mutex_unlock(info->write);
		return (DEAD);
	}
	st_unlock_threads(info);
	return (ALIVE);
}

t_bool	print_or_die(t_info *info, long int time, int action)
{
	if (info->time_to_die > time - info->last_eat)
		return (print_action(info, time, action));
	else
		return (print_action(info, time, DYING));
	return (ALIVE);
}
