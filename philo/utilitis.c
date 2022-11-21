/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilitis.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:05:01 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/21 16:05:05 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
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
