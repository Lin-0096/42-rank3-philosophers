/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:17:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/17 14:38:00 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_and_exit(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (!parse_argv(argc, argv, &data))
		print_and_exit("Error: invalid arguments");
	if (!init_data(&data))
		print_and_exit("Error: init data failed");
	if (!init_philo(&data))
		print_and_exit("Error: init philo failed");
	if (!start_thread(&data, &monitor))
	{
		cleanup_all_mutex_and_free(&data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data.number_of_philo)
		pthread_join(data.philo[i++].thread_id, NULL);
	pthread_join(monitor, NULL);
	destroy_last_mealtime_mutex(&data, data.number_of_philo - 1);
	cleanup_all_mutex_and_free(&data);
	return (EXIT_SUCCESS);
}
