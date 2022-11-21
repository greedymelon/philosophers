/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:51 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:03:53 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	DYING,
};

typedef struct s_time
{
	long int	start;
	long int	last_eat;
	long int	corr_eat;
}t_time;

typedef struct s_info
{	
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				n_times_eat;
	int				n_philo;
	int				philo_id;
	int				schr_box;
	int				therad_fail;
	pthread_t		philo;
	pthread_mutex_t	*dying;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write;
}	t_info;

/* clean_up.c */
void		mutex_clean(pthread_mutex_t *m1, pthread_mutex_t *m2,
				pthread_mutex_t *m3, int num);
void		clean_fork(pthread_mutex_t *forks, int num);
/* init.c */
void		init_philo_info(t_info *info, char **argv);
int			init_mutex(t_info *info, pthread_mutex_t *dying,
				pthread_mutex_t	*write, pthread_mutex_t *forks);
/* input_check.c */
int			right_input(int argc, char **argv);
/* philo_action.c */
t_bool		sleep_act(t_time *times, long int time, t_info *infos);
void		*unlock_fork(t_info *infos, int fork_fir, int fork_sec);
t_bool		dead_or_print(t_info *infos, int action, t_time *times);
t_bool		fork_or_die(t_info *infos, t_time *times, int fork_fir,
				int fork_sec);
t_bool		eat_or_die(t_info *infos, t_time *times);
/* philo_routine.c */
void		*routine_even(void *info);
void		*routine_odd(void *info);
/* print.c */
t_bool		print_action(t_info *info, int action, t_time *times);
/* simulation.c */
void		start_simulation(t_info *info);
/* time.c */
long int	time_msec(void);
/* utilit.c */
size_t		ft_strlen(const char *s);
char		*ft_ltoa(int long n);
int			ft_isspace(int c);

#endif
