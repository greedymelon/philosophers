#include "philo.h"

static void	copy(char *num, int n, int i)
{
	if (n < 0)
	{
		num[0] = '-';
		while (i > 0)
		{
			num[i] = '0' - n % 10;
			n /= 10;
			i--;
		}
	}
	else
	{
		while (i > 0)
		{
			num[i - 1] = '0' + n % 10;
			n /= 10;
			i--;
		}
	}
}

static void	ft_putnbr_fd(int n, int fd)
{
	char	num[11];
	int		count;

	if (n == 0)
		write (fd, "0", 1);
	else
	{
		count = ft_intlen(n);
		copy(num, n, count);
		if (n < 0)
			write (fd, num, count + 1);
		else
			write (fd, num, count);
	}
}

static void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	while (s[size])
		size++;
	if (s == NULL)
		return ;
	write (fd, s, size);
}

void	print_action(int philo, char *action, int time)
{
	ft_putnbr_fd (philo, 1);
	ft_putstr_fd (action, 1);
	ft_putnbr_fd (time, 1);
	write (1, "\n", 1);
}
