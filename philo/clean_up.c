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
