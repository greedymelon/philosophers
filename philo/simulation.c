/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:30 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:04:32 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	st_create_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info[0].n_philo)
	{
		if (info[i].philo_id % 2 == 0)
			pthread_create(&(info[i]).philo, NULL, &routine_even, &info[i]);
		else
			pthread_create(&(info[i]).philo, NULL, &routine_odd, &info[i]);
		i++;
	}
}

static void	st_philo_join(t_info *infos)
{
	int	i;

	i = 0;
	while (i < infos[0].n_philo)
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

	if (pthread_create(&monitor, NULL, &st_monitoring, info))
		return ;
	st_create_thread(info);
	pthread_join(monitor, NULL);
	st_philo_join(info);
}
