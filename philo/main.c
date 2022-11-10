#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info[201];
	pthread_mutex_t	write_die;
	pthread_mutex_t	forks[201];

	if (!right_input(argc, argv))
		return (1);
	if (!pthread_mutex_init(&write_die, NULL));
		return (2);
	if (!init_info(&info, argv, &write_die, &forks))
	{	
		pthread_mutex_destroy(&write_die);
		return (3);
	}
	if (!thread_init(&info))
	{
		mutex_clean(&write_die, &forks);
		return (4);
	}
	if (start_simulation(&info, &start))

}