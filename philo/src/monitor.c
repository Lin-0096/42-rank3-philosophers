/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:45:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/11 23:54:07 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_mealtime(t_philo *philo)
{
	long	last_mealtime;

	pthread_mutex_lock(&philo->last_mealtime_mutex);
	last_mealtime = philo->last_mealtime;
	pthread_mutex_unlock(&philo->last_mealtime_mutex);
	return (last_mealtime);
}

void *monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	last_mealtime;

	data = (t_data *)arg;
	while (1)
	{
		usleep(1000); //void busy waiting
		if (check_death(data))
			break ;
		i = -1;
		while (++i < data->number_of_philo)
		{
			last_mealtime = get_last_mealtime(&data->philo[i]);
			if (get_current_time() - last_mealtime > data->time_to_die)
			{
				pthread_mutex_lock(&data->died_mutex);
				data->someone_died = 1;
				print_status(&data->philo[i], "died");
				pthread_mutex_unlock(&data->died_mutex);
				break ;
			}
		}
	}
	return (NULL);
}
