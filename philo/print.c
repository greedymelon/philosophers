#include "philo.h"

void	ft_strlcat(char *dst, const char *src, size_t dstsize)
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
	int	size;

	size = 0;
	if (s == NULL)
		return ;
	while (s[size])
		size++;
	write (fd, s, size);
}

int	print_action(t_info	*infos, int action_n, long int time)
{
	const char		action[4][18] = {" has taken a fork", " is eating",
		" is sleeping", " is thinking"};
	char			*print_str;

	print_str = st_strjoin3(ft_ltoa(time),
			ft_ltoa(infos->philo_id), action[action_n]);
	pthread_mutex_lock(infos->dying);
	if (infos->schr_box == DEAD)
	{
		pthread_mutex_unlock(infos->dying);
		free(print_str);
		return (DEAD);
	}
	pthread_mutex_unlock(infos->dying);
	ft_putstr_fd(print_str, 1);
	free(print_str);
	return (ALIVE);
}

void	print_dead(long int time_start, long int time, t_info *infos)
{
	char		*print_str;
	long int	now;

	now = time_msec() - time_start;
	if (now - time > 10)
	{
		pthread_mutex_lock(infos->write);
		ft_putstr_fd("ERROR TIME\n", 2);
		ft_putstr_fd(ft_ltoa(now - time), 2);
		pthread_mutex_unlock(infos->write);
		return ;
	}	
	print_str = st_strjoin3(ft_ltoa(time), ft_ltoa(infos->philo_id), " Dead");
	pthread_mutex_lock(infos->write);
	ft_putstr_fd(print_str, 1);
	pthread_mutex_unlock(infos->write);
	free(print_str);
}
