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
	DEAD,
	ALIVE,
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
	long int	start;
	long int	last_eat;
	long int	corr_eat;
}t_time;

typedef struct s_info
{	
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int				n_times_eat;
	int				n_philo;
	int				philo_id;
	int				schr_box;
	pthread_t		philo;
	pthread_mutex_t	*dying;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write;
}	t_info;

int			init_info(t_info *info, char **argv, pthread_mutex_t *write_die,
			pthread_mutex_t *forks);
int			ft_isdigit(int c);
int			ft_atol(const char *str);
char		*ft_ltoa(int long n);
size_t		ft_strlen(const char *s);
int			right_input(int argc, char **argv);
int			print_action(t_info *info, int action, long int time);
int			thread_init(t_info *info);
int			mutex_init(int n_philo);
void		*routine_even(void *info);
void		*routine_odd(void *info);
void		mutex_clean(pthread_mutex_t *m1, pthread_mutex_t *m2,
		pthread_mutex_t *m3, int num);
void		start_simulation(t_info *info);
void		init_philo_info(t_info *info, char **argv);
int			init_mutex(t_info *info, pthread_mutex_t *dying,
		pthread_mutex_t	*write, pthread_mutex_t *forks);
int			fork_or_die(t_info *infos, t_time *times);
int			eat_or_die(t_info *infos, t_time *times);
int			sleep_or_die(t_info *infos, t_time *times);
int			think_or_die(t_info *infos, t_time *times);
long int	time_msec(void);
void		print_dead(long int time, t_info	*infos);
#endif