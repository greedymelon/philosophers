/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:01:51 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 18:31:55 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	st_putnum(const char *str, long int i)
{
	long int	num;

	num = *str - '0';
	str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num * i);
}

static long int	ft_atol(const char *str)
{
	int	i;

	i = 1;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		i = -1;
		str++;
	}
	if (*str >= '0' && *str <= '9')
		return (st_putnum(str, i));
	return (0);
}

static int	st_forks_init(pthread_mutex_t *forks, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{	
			clean_fork(forks, i);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_philo_info(t_info *info, char **argv)
{
	int				i;
	int				n_philo;

	i = 0;
	n_philo = ft_atol(argv[1]);
	while (i < n_philo)
	{
		info[i].n_philo = n_philo;
		info[i].time_to_die = ft_atol(argv[2]);
		info[i].time_to_eat = ft_atol(argv[3]);
		info[i].time_to_sleep = ft_atol(argv[4]);
		info[i].schr_box = ALIVE;
		if (argv[5])
			info[i].n_times_eat = ft_atol(argv[5]);
		else
			info[i].n_times_eat = -1;
		info[i].philo_id = i + 1;
		info[i].theard_fail = 0;
		i++;
	}
}

int	init_mutex(t_info *info, pthread_mutex_t *dying, pthread_mutex_t *writes,
		pthread_mutex_t *forks )
{
	int	i;

	i = 0;
	if (pthread_mutex_init(dying, NULL))
		return (0);
	if (pthread_mutex_init(writes, NULL))
	{	
		pthread_mutex_destroy(dying);
		return (0);
	}
	if (!st_forks_init(forks, info[0].n_philo))
	{
		mutex_clean(dying, writes, NULL, 0);
		return (0);
	}
	while (i < info[0].n_philo)
	{
		info[i].dying = dying;
		info[i].fork = forks;
		info[i].write = writes;
		i++;
	}
	return (1);
}
