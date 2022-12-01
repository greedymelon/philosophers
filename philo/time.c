/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:42 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 14:58:56 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

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

void	ft_wait_ms(int time)
{
	long int	start;

	start = time_msec();
	while (time > time_msec() - start)
	{
		usleep(250);
	}
}
