/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 15:14:15 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/30 17:16:43 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	st_set_dead(t_info *infos)
{
	int	i;

	i = 0;
	while (i < infos[0].n_philo)
	{
		infos[i].schr_box = DEAD;
		i++;
	}
}

int	thread_fail(t_info *infos)
{
	pthread_mutex_lock(infos->dying);
	if (infos->theard_fail)
	{
		st_set_dead(infos);
		pthread_mutex_unlock(infos->dying);
		return (1);
	}
	pthread_mutex_unlock(infos->dying);
	return (0);
}

int	st_check_dead(t_info *infos)
{
	int	i;
	int	all_eat;

	i = 0;
	all_eat = 0;
	while (i < infos[0].n_philo)
	{
		if (infos[i].schr_box == DEAD)
		{	
			st_set_dead(infos);
			pthread_mutex_unlock(infos[0].dying);
			return (DEAD);
		}
		if (infos[i].n_times_eat == 0)
			all_eat++;
		i++;
	}
	if (all_eat == infos[0].n_philo)
		return (DEAD);
	return (ALIVE);
}

void	*monitoring(void *info)
{
	t_info	*infos;

	infos = info;
	if (thread_fail(infos))
		return (NULL);
	while (ALIVE)
	{
		ft_wait_ms(infos->time_to_die / 2);
		pthread_mutex_lock(infos->dying);
		if (st_check_dead(infos) == DEAD)
			return (NULL);
		pthread_mutex_unlock(infos->dying);
	}
	return (NULL);
}
