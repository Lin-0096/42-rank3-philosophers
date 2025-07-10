/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:51 by linliu            #+#    #+#             */
/*   Updated: 2025/07/10 17:08:41 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy_forks(t_data *data, int i)
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
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->died_mutex);
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
