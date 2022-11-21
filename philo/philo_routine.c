/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 18:57:38 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 19:04:03 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	st_calc_next(t_info *infos)
{
	if (infos->philo_id < infos->n_philo)
		return (infos->philo_id);
	return (0);
}

int	thread_fail(t_info *infos)
{
	pthread_mutex_lock(infos->dying);
	if (infos->theard_fail)
	{
		pthread_mutex_unlock(infos->dying);
		return (1);
	}
	pthread_mutex_unlock(infos->dying);
	return (0);
}

void	*routine_even(void *info)
{
	t_info		*infos;
	int			fork_right;
	long int	eat;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	usleep(10);
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	eat = infos->start;
	while (1)
	{
		if (fork_or_die(infos, eat, fork_right, infos->philo_id - 1) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &eat) == DEAD)
			return (unlock_fork(info, infos->philo_id - 1, fork_right));
		unlock_fork(info, infos->philo_id - 1, fork_right);
		if (dead_or_print(infos, SLEEP, eat) == DEAD)
			return (NULL);
		if (sleep_act(eat, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, eat) == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	*routine_odd(void *info)
{
	t_info		*infos;
	int			fork_right;
	long int	eat;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	eat = infos->start;
	while (1)
	{
		if (fork_or_die(infos, eat, infos->philo_id - 1, fork_right) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &eat) == DEAD)
			return (unlock_fork(info, fork_right, infos->philo_id - 1));
		unlock_fork(info, fork_right, infos->philo_id - 1);
		if (dead_or_print(infos, SLEEP, eat) == DEAD)
			return (NULL);
		if (sleep_act(eat, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, eat) == DEAD)
			return (NULL);
	}
	return (NULL);
}
