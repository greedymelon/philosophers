#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_bool
{
	YES,
	NO,
}	t_bool;

enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
};

typedef struct s_time
{
	int	start;
	int	last_eat;
	int	corr_eat;
}t_time;

typedef struct s_info
{	
	int				time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_times_eat;
	int				n_philo;
	int				philo_id;
	t_bool			dead;
	pthread_t		philo;
	pthread_mutex_t	**fork;
	pthread_mutex_t	*write_die;
}	t_info;

int		init_info(t_info **info, char **argv, pthread_mutex_t **forks,
pthread_mutex_t *write_die);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
int		right_input(int argc, char **argv);
void	print_action(int philo, char *action, int time);
int		thread_init(t_info **info);
int		mutex_init(int n_philo);
void	routine_even(void *info);
void	routine_odd(void *info);

#endif