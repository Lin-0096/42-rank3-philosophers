/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:39:46 by linliu            #+#    #+#             */
/*   Updated: 2025/07/10 19:59:35 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	parse_argv(int argc, char **argv, t_data *data)
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
	data->number_of_philo = read_num(argv[1]);
	data->time_to_die = read_num(argv[2]);
	data->time_to_eat = read_num(argv[3]);
	data->time_to_sleep = read_num(argv[4]);
	if (argc == 6)
		data->num_must_eat = read_num(argv[5]);
	else if (argc == 5)
		data->num_must_eat = -1;
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->fork)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0) //success 0;
			return (free_and_destroy_forks(data, i - 1), 0); //should -1 here??
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (free_and_destroy_forks(data, data->number_of_philo - 1), 0); //should -1 here??
	data->someone_died = 0;
	if (pthread_mutex_init(&data->died_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (free_and_destroy_forks(data, data->number_of_philo - 1), 0);
	}
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (cleanup_all_mutex_and_free(data), 0);
	data->start_time = get_current_time();//
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].last_mealtime = data->start_time;
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1) % data->number_of_philo];
		data->philo[i].data = data;
		//no need to initlize thread_id, it will be given value in pthread_create!!
		i++;
	}
	return (1);
}
