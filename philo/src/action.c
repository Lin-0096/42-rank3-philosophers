/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:45:18 by linliu            #+#    #+#             */
/*   Updated: 2025/07/11 21:19:55 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		//should i check eat_count and protect eat_count??
		
		if (check_death(philo->data))
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
