/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:30 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 18:56:27 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	st_set_fail(t_info *info)
{
	int	i;

	i = 0;
	while (i < info[0].n_philo)
	{
		info[i].theard_fail = 1;
		i++;
	}
}

static int	st_create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info[0].n_philo)
	{
		if (info[i].philo_id % 2 == 0)
		{	
			if (pthread_create(&(info[i]).philo, NULL, &routine_even, &info[i]))
				break ;
		}
		else
		{	
			if (pthread_create(&(info[i]).philo, NULL, &routine_odd, &info[i]))
				break ;
		}
		i++;
	}
	if (i > info[0].n_philo)
		st_set_fail(info);
	return (i);
}

static void	st_philo_join(t_info *infos, int philo)
{
	int	i;

	i = 0;
	while (i < philo)
	{
		pthread_join(infos[i].philo, NULL);
		i++;
	}
}

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

static void	*st_monitoring(void *info)
{
	int		i;
	int		all_eat;

	if (thread_fail((t_info *)info))
		return (NULL);
	while (ALIVE)
	{
		i = 0;
		all_eat = 0;
		pthread_mutex_lock(((t_info *)info)[0].dying);
		while (i < ((t_info *)info)[0].n_philo)
		{
			if (((t_info *)info)[i].schr_box == DEAD)
			{	
				st_set_dead(((t_info *)info));
				pthread_mutex_unlock(((t_info *)info)[0].dying);
				return (NULL);
			}
			if (((t_info *)info)[i++].n_times_eat == 0)
				all_eat++;
		}
		pthread_mutex_unlock(((t_info *)info)[0].dying);
		if (all_eat == ((t_info *)info)[0].n_philo)
			return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_info *info)
{
	pthread_t	monitor;
	int			thread_created;

	pthread_mutex_lock(info->dying);
	if (pthread_create(&monitor, NULL, &st_monitoring, info))
	{
		pthread_mutex_unlock(info->dying);
		return ;
	}	
	thread_created = st_create_thread(info);
	pthread_mutex_unlock(info->dying);
	pthread_join(monitor, NULL);
	st_philo_join(info, thread_created);
}
