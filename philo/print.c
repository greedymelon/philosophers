#include "philo.h"


static void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	if (s == NULL)
		return ;
	while (s[size])
		size++;
	write (fd, s, size);
}

void	print_action(t_info	*infos, int action_n, int time)
{
	const char		action = {"has taken a fork", "is eating",
		" is sleeping", "is thinking", "died"};
	
	char *print_string;

	print_string = string_join(ft_itoa(time), ft_itoa(infos->philo_id), action[action_n]);
	ft_putnbr_sp_fd (print_string, 1);
	free(print_string)
}
