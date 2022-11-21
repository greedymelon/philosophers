/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:33 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:03:36 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	st_calc_next(t_info *infos)
{
	if (infos->philo_id < infos->n_philo)
		return (infos->philo_id);
	return (0);
}

void	*routine_even(void *info)
{
	t_info	*infos;
	int		fork_right;
	t_time	times;

	infos = info;
	fork_right = st_calc_next(infos);
	times.start = time_msec();
	times.last_eat = times.start;
	while (1)
	{
		if (fork_or_die(infos, &times, fork_right, infos->philo_id - 1) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &times) == DEAD)
			return (unlock_fork(info, infos->philo_id - 1, fork_right));
		unlock_fork(info, infos->philo_id - 1, fork_right);
		if (dead_or_print(infos, SLEEP, &times) == DEAD)
			return (NULL);
		if (sleep_act(&times, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, &times) == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	*routine_odd(void *info)
{
	t_info	*infos;
	int		fork_right;
	t_time	times;

	infos = info;
	fork_right = st_calc_next(infos);
	times.start = time_msec();
	times.last_eat = times.start;
	while (1)
	{
		if (fork_or_die(infos, &times, infos->philo_id - 1, fork_right) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &times) == DEAD)
			return (unlock_fork(info, fork_right, infos->philo_id - 1));
		unlock_fork(info, fork_right, infos->philo_id - 1);
		if (dead_or_print(infos, SLEEP, &times) == DEAD)
			return (NULL);
		if (sleep_act(&times, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, &times) == DEAD)
			return (NULL);
	}
	return (NULL);
}
