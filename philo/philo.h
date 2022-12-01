/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:03:51 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/12/01 18:23:44 by dmonfrin      ########   odam.nl         */
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

enum e_forkst
{
	AVAILABLE,
	UNAVAILABLE,
	NONE_F = -1,
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
	long int		last_eat;
	int				theard_fail;
	int				*fork_lock;
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
int			init_philo_info(t_info *info, char **argv, int *fork_lock);
int			init_mutex(t_info *info, pthread_mutex_t *dying,
				pthread_mutex_t	*write, pthread_mutex_t *forks);
/* input_check.c */
int			right_input(int argc, char **argv);
/* monitoring.c */
void		*monitoring(void *info);
/* philo_action.c */
t_bool		sleep_act(t_info *info, long int start, long int time);
t_bool		print_or_die(t_info *info, long int time, int action);
t_bool		fork_or_die(t_info *info, int fork_fir, int fork_sec);
t_bool		eat_or_die(t_info *info, int *meal_n);
t_bool		sleep_or_die(t_info *info);
/* philo_routine.c */
int			thread_fail(t_info *info);
void		*routine_even(void *info);
void		*routine_odd(void *info);
void		*routine_oddo(void *info);
/* print.c */
t_bool		print_action(t_info *info, long int time, int action);
/* simulation.c */
void		start_simulation(t_info *info);
/* time.c */
long int	time_msec(void);
void		ft_wait_ms(int time);
/* utilit.c */
long int	ft_atol(const char *str);
void		*unlock_fork(t_info *info, int fork_fir, int fork_sec);
void		set_fork_status(t_info *info, int fork_1, int fork_2, int status);

#endif
