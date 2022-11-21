/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 18:06:32 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_bool	sleep_act(long int eat, long int time, t_info *infos)
{
	long int	start;

	start = time_msec();
	while (time > time_msec() - start)
	{
		usleep(100);
		pthread_mutex_lock(infos->dying);
		if (infos->schr_box == DEAD)
		{
			pthread_mutex_unlock(infos->dying);
			return (DEAD);
		}
		pthread_mutex_unlock(infos->dying);
		if (infos->time_to_die <= time_msec() - infos->start - eat)
			return (print_action(infos, DYING, eat));
	}
	return (ALIVE);
}

void	*unlock_fork(t_info *infos, int fork_fir, int fork_sec)
{
	pthread_mutex_unlock(&(infos->fork)[fork_fir]);
	pthread_mutex_unlock(&(infos->fork)[fork_sec]);
	return (NULL);
}

t_bool	dead_or_print(t_info *infos, int action, long int eat)
{
	if (infos->time_to_die > time_msec() - infos->start - eat)
		return (print_action(infos, action, eat));
	else
	{
		print_action(infos, DYING, eat);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	fork_or_die(t_info *infos, long int eat, int fork_fir, int fork_sec)
{
	pthread_mutex_lock(&(infos->fork)[fork_fir]);
	if (dead_or_print(infos, FORK, eat) == DEAD)
	{
		pthread_mutex_unlock(&(infos->fork)[fork_fir]);
		return (DEAD);
	}
	pthread_mutex_lock(&(infos->fork)[fork_sec]);
	if (dead_or_print(infos, FORK, eat) == DEAD)
	{
		unlock_fork(infos, fork_fir, fork_sec);
		return (DEAD);
	}
	return (ALIVE);
}

t_bool	eat_or_die(t_info *infos, long int *eat)
{
	int	n_eat;

	if (dead_or_print(infos, EAT, *eat) == DEAD)
		return (DEAD);
	*eat = time_msec() - infos->start;
	if (sleep_act(*eat, infos->time_to_eat, infos) == DEAD)
		return (DEAD);
	pthread_mutex_lock(infos->dying);
	infos->n_times_eat--;
	n_eat = infos->n_times_eat;
	pthread_mutex_unlock(infos->dying);
	if (n_eat == 0)
		return (DEAD);
	return (ALIVE);
}
