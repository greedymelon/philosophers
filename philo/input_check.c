#include "philo.h"

static int	is_all_numb(char *str)
{
	int	i;
	
	i = 0;
	if (!str[i])
		return (0);
	while(str[i])
		if(!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	right_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_all_numb(argv[i]))
			return (0);
		i++;
	}
	return (1);
}