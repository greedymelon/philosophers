/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:02:47 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 13:22:49 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*st_one_philo(void *info)
{
	t_info		*infos;
	long int	eat;
	long int	fork_time;

	infos = info;
	infos->start = time_msec();
	eat = 0;
	pthread_mutex_lock(infos->fork);
	fork_time = time_msec() - infos->start;
	print_or_die(infos, fork_time, eat, FORK);
	sleep_act(info, fork_time, eat, infos->time_to_die);
	print_or_die(infos, time_msec() - infos->start, eat, DYING);
	pthread_mutex_unlock(infos->fork);
	return (NULL);
}

static void	st_fake_simulation(t_info *info)
{
	pthread_t	philo_alone;

	if (pthread_create(&philo_alone, NULL, &st_one_philo, info))
		return ;
	pthread_join(philo_alone, NULL);
}

int	main(int argc, char **argv)
{
	t_info			info[201];
	pthread_mutex_t	writes;
	pthread_mutex_t	dying;
	pthread_mutex_t	forks[201];

	if (!right_input(argc, argv))
		return (1);
	if (init_philo_info(&info[0], argv))
		return (2);
	if (!init_mutex(&info[0], &dying, &writes, &forks[0]))
		return (3);
	if (info[0].n_philo == 1)
		st_fake_simulation(&info[0]);
	else
		start_simulation(&info[0]);
	mutex_clean(&writes, &dying, &forks[0], info[0].n_philo);
	return (0);
}
