/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:42 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/23 17:26:13 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

static long int	st_tv_msec(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

long int	time_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (st_tv_msec(&tv));
}
