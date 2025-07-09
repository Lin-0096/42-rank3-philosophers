/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:17:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/09 17:31:39 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
		cleanup_all_mutex_and_free(&data);
		printf("Error: init data failed\n");
		return (EXIT_FAILURE);
	}
	//start_thread (pthread_creat(),philo_routine)
	//start_monitor (pthread_creat(), monitor)
	//join_thread(pthread_join())
	//cleanup_all_mutex_and_free(&data);
	return (EXIT_SUCCESS);
}
