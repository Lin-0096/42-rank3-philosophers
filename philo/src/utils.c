/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:50:56 by linliu            #+#    #+#             */
/*   Updated: 2025/07/09 17:18:16 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_and_destroy_forks(t_data *data, int i)
{
	if (data->fork)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i--;
		}
		free(data->fork);
	}
}

void	cleanup_all_mutex_and_free(t_data *data)
{
	free_and_destroy_forks(data, data->number_of_philo - 1);
	pthread_mutex_destroy(&data->print);
	if (data->philo)
		free(data->philo);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL); //fills the tv struct with the current system time
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
	//1000L ensures the result is a long to avoid overflow.
	//convert seconds to milliseconds. convert microseconds to milliseconds. return total time then
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
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (free_and_destroy_forks(data, data->number_of_philo - 1), 0); //should -1 here??
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (cleanup_all_mutex_and_free(data), 0);
	data->start_time = get_current_time();//
	data->someone_died = 0;
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
		i++;
	}
	return (1);
}
