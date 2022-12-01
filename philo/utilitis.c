/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilitis.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:05:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 15:22:50 by dmonfrin      ########   odam.nl         */
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

void	*unlock_fork(t_info *info, int fork_fir, int fork_sec)
{
	set_fork_status(info, fork_fir, fork_sec, AVAILABLE);
	pthread_mutex_unlock(&(info->fork)[fork_fir]);
	pthread_mutex_unlock(&(info->fork)[fork_sec]);
	return (NULL);
}

void	set_fork_status(t_info *info, int fork_1, int fork_2, int status)
{
	pthread_mutex_lock(info->dying);
	info->fork_lock[fork_1] = status;
	if (fork_2 >= 0)
		info->fork_lock[fork_2] = status;
	pthread_mutex_unlock(info->dying);
}
