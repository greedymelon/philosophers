#include "philo.h"

long int	tv_msec(struct timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

long int	time_msec(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv_msec(&tv));
}

int	calc_next(t_info *infos)
{
	if (infos->philo_id < infos->n_philo)
		return (infos->philo_id);
	return (0);
}

void	*routine_even(void *info)
{
	t_info	*infos;
	int		fork_right;
	t_time	times;

	infos = info;
	fork_right = calc_next(infos);
	times.start = time_msec();
	times.last_eat = times.start;
	while (1)
	{
		pthread_mutex_lock(&(infos->fork)[fork_right]);
		if (dead_or_print(infos, FORK, &times) == DEAD)
		{
			pthread_mutex_unlock(&(infos->fork)[fork_right]);
			return (NULL);
		}
		pthread_mutex_lock(&(infos->fork)[infos->philo_id - 1]);
		if (eat_or_die(infos, &times) == DEAD)
		{
			pthread_mutex_unlock(&(infos->fork)[fork_right]);
			pthread_mutex_unlock(&(infos->fork)[infos->philo_id - 1]);
			return (NULL);
		}
		pthread_mutex_unlock(&(infos->fork)[fork_right]);
		pthread_mutex_unlock(&(infos->fork)[infos->philo_id - 1]);

		if (dead_or_print(infos, SLEEP, &times) == DEAD)
			return (NULL);
		if (sleep_act(&times, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, &times) == DEAD)
			return (NULL);
		usleep(0);
	}
	return (NULL);
}

void	*routine_odd(void *info)
{
	t_info	*infos;
	int		fork_right;
	t_time	times;

	infos = info;
	fork_right = calc_next(infos);
	times.start = time_msec();
	times.last_eat = times.start;
	while (1)
	{
		pthread_mutex_lock(&(infos->fork)[infos->philo_id - 1]);
		if (dead_or_print(infos, FORK, &times) == DEAD)
		{
			pthread_mutex_unlock(&(infos->fork)[infos->philo_id - 1]);
			return (NULL);
		}
		if (time_msec() - times.start - times.last_eat > infos->time_to_die / 2)
			usleep(10);
		pthread_mutex_lock(&(infos->fork)[fork_right]);
		if (eat_or_die(infos, &times) == DEAD)
		{
			pthread_mutex_unlock(&(infos->fork)[fork_right]);
			pthread_mutex_unlock(&(infos->fork)[infos->philo_id - 1]);
			return (NULL);
		}
		pthread_mutex_unlock(&(infos->fork)[fork_right]);
		pthread_mutex_unlock(&(infos->fork)[infos->philo_id - 1]);
		if (dead_or_print(infos, SLEEP, &times) == DEAD)
			return (NULL);
		if (sleep_act(&times, infos->time_to_sleep, infos) == DEAD)
			return (NULL);
		if (dead_or_print(infos, THINK, &times) == DEAD)
			return (NULL);
		usleep(0);
	}
	return (NULL);
}
