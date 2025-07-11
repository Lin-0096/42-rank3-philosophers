/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:17:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/11 23:05:22 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (!parse_argv(argc, argv, &data))
	{
		printf("Error: invalid arguments\n");
		return (EXIT_FAILURE);
	}
	if (!init_data(&data))
	{
		printf("Error: init data failed\n");
		return (EXIT_FAILURE);
	}
	if (!init_philo(&data))
	{
		printf("Error: init philo failed\n");
		return (EXIT_FAILURE);
	}
	if (!start_thread(&data))
	{
		cleanup_all_mutex_and_free(&data);
		//should i close the thread that i opened before return???
		return (EXIT_FAILURE);
	}
	//start_monitor (pthread_creat(), monitor)
	pthread_t monitor;
	pthread_create(&monitor, NULL, monitor_routine, &data);
	//join_thread (pthread_join())

	//test mutex
	for (int i = 0; i < data.number_of_philo; i++)
	{
		pthread_join(data.philo[i].thread_id, NULL);
	}
	pthread_join(monitor, NULL);

	destroy_last_mealtime_mutex(&data, data.number_of_philo - 1);
	cleanup_all_mutex_and_free(&data);
	return (EXIT_SUCCESS);
}


/*
test status of mutex:
	int i = 0;
	while (i < data.number_of_philo)
	{
		printf("Philosopher %d:\n", data.philo[i].id);
		printf("Left fork addr : %p\n", (void *)data.philo[i].left_fork);
		printf("Right fork addr: %p\n", (void *)data.philo[i].right_fork);
		i++;
	}
*/
