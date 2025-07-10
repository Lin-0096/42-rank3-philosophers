/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:45:18 by linliu            #+#    #+#             */
/*   Updated: 2025/07/10 19:54:55 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		//thinking, doing nothing, just check status and print status
		print_status(philo, "is thinking");
		//take left fork
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		//take right fork
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		//eating
		//unlock fork
		//eat_count++
		//sleeping
		usleep(1000);
	}

}

int start_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, philo_routine, &data->philo[i]) != 0)
		{
			printf("Error: failed to create thread for philosopher %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
