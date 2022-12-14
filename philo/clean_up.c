/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:01:33 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:01:36 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_clean(pthread_mutex_t *m1, pthread_mutex_t *m2,
	pthread_mutex_t *m3, int num)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(m1);
	pthread_mutex_destroy(m2);
	while (i < num)
	{
		pthread_mutex_destroy(&m3[i]);
		i++;
	}
}

void	clean_fork(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
