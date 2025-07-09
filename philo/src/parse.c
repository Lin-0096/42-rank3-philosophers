/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:18:04 by linliu            #+#    #+#             */
/*   Updated: 2025/07/09 10:43:02 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	read_num(char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!*str)
		return (-1);
	while(*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return ((int)result);
}

int	parse_argv(int argc, char **argv, t_data *argvs)
{
	int	i;
	int	tmp;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		tmp = read_num(argv[i]);
		if (tmp <= 0)
			return (0);
		i++;
	}
	argvs->number_of_philo = read_num(argv[1]);
	argvs->time_to_die = read_num(argv[2]);
	argvs->time_to_eat = read_num(argv[3]);
	argvs->time_to_sleep = read_num(argv[4]);
	if (argc == 6)
		argvs->num_must_eat = read_num(argv[5]);
	else if (argc == 5)
		argvs->num_must_eat = -1;
	return (1);
}
