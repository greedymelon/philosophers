/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 16:02:09 by dmonfrin      #+#    #+#                 */
/*   Updated: 2022/11/25 16:29:04 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	is_all_numb(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
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
	if (ft_atol(argv[1]) > 200 || ft_atol(argv[1]) < 1)
		return (0);
	if (argv[5] && ft_atol(argv[5]) < 1)
		return (0);
	if (ft_atol(argv[2]) < 1 || ft_atol(argv[3]) < 0 || ft_atol(argv[4]) < 0)
		return (0);
	return (1);
}
