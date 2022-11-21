/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:04:12 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 18:19:20 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static void	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	if (dstsize != 0 && dst_len < dstsize)
	{
		while (dst_len + i < dstsize - 1 && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
}

static char	*st_strjoin3(char *s1, char *s2, const char *s3)
{
	char	*nws;
	size_t	s1_size;
	size_t	nwssize;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	nwssize = s1_size + ft_strlen(s2) + ft_strlen(s3) + 3;
	nws = (char *)malloc(nwssize * sizeof(char));
	if (nws == NULL)
		return (NULL);
	nws[0] = '\0';
	ft_strlcat(nws, s1, nwssize);
	nws[s1_size] = ' ';
	nws[s1_size + 1] = '\0';
	ft_strlcat(nws, s2, nwssize);
	ft_strlcat(nws, (char *)s3, nwssize);
	nws[nwssize - 2] = '\n';
	nws[nwssize - 1] = '\0';
	free(s1);
	free(s2);
	return (nws);
}

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	size;

	if (s == NULL)
		return ;
	size = ft_strlen(s);
	write (fd, s, size);
}

static t_bool	st_print_error(t_info *infos)
{
	pthread_mutex_lock(infos->dying);
	if (infos->schr_box == DEAD)
	{
		pthread_mutex_unlock(infos->dying);
		pthread_mutex_unlock(infos->write);
		return (DEAD);
	}
	infos->schr_box = DEAD;
	pthread_mutex_unlock(infos->dying);
	ft_putstr_fd("ERROR TIME\n", 2);
	pthread_mutex_unlock(infos->write);
	return (DEAD);
}

t_bool	print_action(t_info *infos, int action_n, long int eat)
{
	const char	action[5][18] = {" has taken a fork", " is eating",
		" is sleeping", " is thinking", " died"};
	char		*print_string;

	pthread_mutex_lock(infos->write);
	if (action_n == DEAD && time_msec() - infos->start - eat
		> infos->time_to_die + 10)
		return (st_print_error(infos));
	pthread_mutex_lock(infos->dying);
	if (infos->schr_box == DEAD)
	{
		pthread_mutex_unlock(infos->dying);
		pthread_mutex_unlock(infos->write);
		return (DEAD);
	}
	print_string = st_strjoin3(ft_ltoa(time_msec() - infos->start),
			ft_ltoa(infos->philo_id), action[action_n]);
	ft_putstr_fd(print_string, 1);
	if (action_n == DYING)
	{	
		infos->schr_box = DEAD;
		pthread_mutex_unlock(infos->dying);
		usleep(1000000);
		pthread_mutex_unlock(infos->write);
		free (print_string);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->dying);
	pthread_mutex_unlock(infos->write);
	free (print_string);
	return (ALIVE);
}
