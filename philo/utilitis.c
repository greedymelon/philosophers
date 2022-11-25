/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilitis.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:05:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 12:51:28 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

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

long int	ft_atol(const char *str)
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

void	ft_wait_ms(int time)
{
	long int	start;

	start = time_msec();
	while (time > time_msec() - start)
	{
		usleep(250);
	}
}

void	*unlock_fork(t_info *infos, int fork_fir, int fork_sec)
{
	pthread_mutex_unlock(&(infos->fork)[fork_fir]);
	pthread_mutex_unlock(&(infos->fork)[fork_sec]);
	return (NULL);
}
