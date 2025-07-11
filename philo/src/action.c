/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:45:18 by linliu            #+#    #+#             */
/*   Updated: 2025/07/11 13:51:58 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// stagger the start of the threads in order to reduce the chance of deadlock
	// if (philo->id % 2 == 0)
	// 	usleep(200);
	while (1)
	{
		if (philo->eat_count >= philo->data->num_must_eat)
		{
			print_status(philo, "has eaten the maximum number of times");
			break;
		}
		//thinking, doing nothing, just check status and print it
		print_status(philo, "is thinking");
		//eating: take both forks, eating, drop forks
		take_forks(philo);
		eating(philo);
		drop_fork(philo);
		//sleeping
		sleeping(philo);
	}
	return (NULL);
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
