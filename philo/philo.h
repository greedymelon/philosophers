#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philo
{
		int				philo_n;
		pthread_mutex_t	fork;
		pthread_t		philo;

}	t_philo;

typedef struct s_info
{	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_eat;
	int				n_philo;
	t_philo			philo[200];
	pthread_mutex_t	write_die;
}	t_info;

void	init_info(t_info *info, char **argv);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
int		right_input(int argc, char **argv);
void	print_action(int philo, char *action, int time);
void	thread_init(t_info *info);
void	mutex_init(t_info *info);

#endif