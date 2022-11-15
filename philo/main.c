#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info[201];
	pthread_mutex_t	writes;
	pthread_mutex_t	dying;
	pthread_mutex_t	forks[201];

	if (!right_input(argc, argv))
		return (1);
	init_philo_info(&info[0], argv);
	if (!init_mutex(&info[0], &dying, &writes, &forks[0]))
		return (2);
	start_simulation(&info[0]);
	mutex_clean(&writes, &dying, &forks[0], info[0].n_philo);
	return (0);
}