/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:51 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 12:52:28 by dmonfrin      ########   odam.nl         */
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

typedef struct s_info
{	
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				n_times_eat;
	int				n_philo;
	int				philo_id;
	int				schr_box;
	long int		start;
	int				theard_fail;
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
int			init_philo_info(t_info *info, char **argv);
int			init_mutex(t_info *info, pthread_mutex_t *dying,
				pthread_mutex_t	*write, pthread_mutex_t *forks);
/* input_check.c */
int			right_input(int argc, char **argv);
/* monitoring.c */
void		*monitoring(void *info);
/* philo_action.c */
t_bool		sleep_act(t_info *infos, long int start,
				long int eat, long int time);
t_bool		print_or_die(t_info *infos, long int time, long int eat,
				int action);
t_bool		fork_or_die(t_info *infos, long int eat, int fork_fir,
				int fork_sec);
t_bool		eat_or_die(t_info *infos, long int *eat);
t_bool		sleep_or_die(t_info *infos, long int eat);
/* philo_routine.c */
int			thread_fail(t_info *infos);
void		*routine_even(void *info);
void		*routine_odd(void *info);
/* print.c */
t_bool		print_action(t_info *info, long int time, long int eat, int action);
/* simulation.c */
void		start_simulation(t_info *info);
/* time.c */
long int	time_msec(void);
/* utilit.c */
long int	ft_atol(const char *str);
void		ft_wait_ms(int time);
void		*unlock_fork(t_info *infos, int fork_fir, int fork_sec);

#endif
