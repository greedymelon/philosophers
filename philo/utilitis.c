#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

static long int	putnum(const char *str, long int i)
{
	long int	num;

	num = *str - '0';
	str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num * i);
}

long int	ft_atol(const char *str)
{
	int	i;

	i = 1;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		i = -1;
		str++;
	}
	if (*str >= '0' && *str <= '9')
		return (putnum(str, i));
	return (0);
}


int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9')));
}


static char	*copy(char *num, long int n, int i)
{
	if (n < 0)
	{
		num[i + 1] = '\0';
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
		num[i] = '\0';
		while (i > 0)
		{
			num[i - 1] = '0' + (n % 10);
			n /= 10;
			i--;
		}
	}
	return (num);
}

static int	ft_longlen(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_ltoa(long int n)
{
	char	*num;
	int		longlen;

	longlen = ft_longlen(n);
	if (n < 0)
		num = malloc((longlen + 2) * sizeof(char));
	else
		num = malloc((longlen + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	if (n != 0)
		return (copy(num, n, longlen));
	num[0] = '0';
	num[1] = '\0';
	return (num);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}