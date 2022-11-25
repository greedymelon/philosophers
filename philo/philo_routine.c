/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 18:57:38 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 15:50:25 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	st_calc_next(t_info *infos)
{
	if (infos->philo_id < infos->n_philo)
		return (infos->philo_id);
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
	fork_right = st_calc_next(infos);
	infos->start = time_msec();
	eat = 0;
	sleep_act(info, eat, eat, infos->time_to_eat / 2);
	while (1)
	{
		if (fork_or_die(infos, eat, fork_right, infos->philo_id - 1) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &eat) == DEAD)
			return (unlock_fork(info, infos->philo_id - 1, fork_right));
		unlock_fork(info, infos->philo_id - 1, fork_right);
		if (sleep_or_die(infos, eat) == DEAD)
			return (NULL);
		if (print_or_die(infos, time_msec() - infos->start, eat, THINK) == DEAD)
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
	eat = 0;
	while (1)
	{
		if (fork_or_die(infos, eat, infos->philo_id - 1, fork_right) == DEAD)
			return (NULL);
		if (eat_or_die(infos, &eat) == DEAD)
			return (unlock_fork(info, fork_right, infos->philo_id - 1));
		unlock_fork(info, fork_right, infos->philo_id - 1);
		if (sleep_or_die(infos, eat) == DEAD)
			return (NULL);
		if (print_or_die(infos, time_msec() - infos->start, eat, THINK) == DEAD)
			return (NULL);
		if (infos->n_philo % 2 != 0)
			sleep_act(infos, time_msec() - infos->start, eat, 1);
	}
	return (NULL);
}
