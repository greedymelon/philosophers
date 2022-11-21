/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:02:47 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 18:57:17 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *info)
{
	t_info		*infos;
	long int	eat;

	infos = info;
	infos->start = time_msec();
	eat = infos->start;
	pthread_mutex_lock(&(infos->fork)[0]);
	dead_or_print(infos, FORK, eat);
	sleep_act(eat, infos->time_to_die - (time_msec() - infos->start), infos);
	dead_or_print(infos, DYING, eat);
	pthread_mutex_unlock(&(infos->fork)[0]);
	return (NULL);
}

void	fake_simulation(t_info *info)
{
	pthread_t	philo_alone;

	if (pthread_create(&philo_alone, NULL, &one_philo, info))
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
	init_philo_info(&info[0], argv);
	if (!init_mutex(&info[0], &dying, &writes, &forks[0]))
		return (2);
	if (info[0].n_philo == 1)
		fake_simulation(&info[0]);
	else
		start_simulation(&info[0]);
	mutex_clean(&writes, &dying, &forks[0], info[0].n_philo);
	return (0);
}
