/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 18:57:38 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 15:29:49 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	st_calc_next(t_info *info)
{
	if (info->philo_id < info->n_philo)
		return (info->philo_id);
	return (0);
}

static int	times_eat(t_info *info)
{
	int	times_eat;

	pthread_mutex_lock(info->dying);
		times_eat = info->n_times_eat;
	pthread_mutex_unlock(info->dying);
	return (times_eat);
}

void	*routine_even(void *info)
{
	t_info		*infos;
	int			fork_right;
	int			meal_n;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	meal_n = times_eat(infos);
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	infos->last_eat = 0;
	sleep_act(info, 0, infos->time_to_eat / 2);
	while (1)
	{
		if (fork_or_die(infos, fork_right, infos->philo_id - 1) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &meal_n) == DEAD)
			return (unlock_fork(info, infos->philo_id - 1, fork_right));
		unlock_fork(info, infos->philo_id - 1, fork_right);
		if (sleep_or_die(infos) == DEAD)
			return (NULL);
		if (print_or_die(infos, time_msec() - infos->start, THINK) == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	*routine_odd(void *info)
{
	t_info		*infos;
	int			fork_right;
	int			meal_n;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	meal_n = times_eat(infos);
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	infos->last_eat = 0;
	while (1)
	{
		if (fork_or_die(infos, infos->philo_id - 1, fork_right) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &meal_n) == DEAD)
			return (unlock_fork(info, fork_right, infos->philo_id - 1));
		unlock_fork(info, fork_right, infos->philo_id - 1);
		if (sleep_or_die(infos) == DEAD)
			return (NULL);
		if (print_or_die(infos, time_msec() - infos->start, THINK) == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	*routine_oddo(void *info)
{
	t_info		*infos;
	int			fork_right;
	int			meal_n;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	meal_n = times_eat(infos);
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	infos->last_eat = 0;
	while (1)
	{
		if (fork_or_die(infos, infos->philo_id - 1, fork_right) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &meal_n) == DEAD)
			return (unlock_fork(info, fork_right, infos->philo_id - 1));
		unlock_fork(info, fork_right, infos->philo_id - 1);
		if (sleep_or_die(infos) == DEAD)
			return (NULL);
		if (print_or_die(infos, time_msec() - infos->start, THINK) == DEAD)
			return (NULL);
		sleep_act(infos, time_msec() - infos->start, 1);
	}
	return (NULL);
}
