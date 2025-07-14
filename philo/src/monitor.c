/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:45:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/14 19:20:26 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_mealtime(t_philo *philo)
{
	long	last_mealtime;

	pthread_mutex_lock(&philo->meal_mutex);
	last_mealtime = philo->last_mealtime;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_mealtime);
}

static int	check_all_full(t_data *data)
{
	int all_full;
	int	i;

	all_full = 1;
	i = -1;
	while (++i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (data->philo[i].eat_count < data->num_must_eat)
			all_full = 0;
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
	}
	if (all_full == 1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("Everyone is full\n");
		pthread_mutex_unlock(&data->print_mutex);
		return	(0);
	}
	return (1);
}

static int	check_starve(t_data *data)
{
	int		i;
	long	last_mealtime;

	i = -1;
	while (++i < data->number_of_philo)
	{
		last_mealtime = get_last_mealtime(&data->philo[i]);
		if (get_current_time() - last_mealtime > data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			print_status(&data->philo[i], "died");
			pthread_mutex_unlock(&data->stop_mutex);
			return (0);
		}
	}
	return (1);
}

void *monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		usleep(1000); //void busy waiting
		if (check_stop(data))
			break ;
		if (!check_starve(data))
			break ;
		if (data->num_must_eat > 0)
		{
			if (!check_all_full(data))
				break ;
		}
	}
	return (NULL);
}
