/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:45:18 by linliu            #+#    #+#             */
/*   Updated: 2025/07/17 15:00:36 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_stop(philo->data))
			break ;
		//thinking, doing nothing, just check status and print it
		print_status(philo, "is thinking");
		//eating: take both forks, eating, drop forks
		take_forks(philo);
		eating(philo);
		drop_fork(philo);
		//sleeping
		sleeping(philo);
		usleep(1000);// Small delay to allow other threads to run
	}
	return (NULL);
}

int start_thread(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, philo_routine, &data->philo[i]) != 0)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);//
			printf("Error: failed to create thread for philosopher %d\n", i);
			while (--i >= 0)
				pthread_join(data->philo[i].thread_id, NULL);//
			return (0);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop_mutex);//
		printf("Error: failed to create monitor thread\n");
		while (i < data->number_of_philo)
			pthread_join(data->philo[i++].thread_id, NULL);//
		i = 0;
		return (0);
	}
	return (1);
}
