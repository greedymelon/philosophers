#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info[201];
	pthread_mutex_t	write;
	pthread_mutex_t	dying;
	pthread_mutex_t	forks[201];

	if (!right_input(argc, argv))
		return (1);
	init_philo_info(&info[0], argv);
	if (!init_mutex(&info[0], &dying, &write, &forks[0]))
		return (2);
	start_simulation(&info[0]);
	mutex_clean(&write, &dying, &forks[0], info[0].n_philo);
	return (0);
}