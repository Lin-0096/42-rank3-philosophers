/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:17:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/08 20:40:56 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>


int	main(int argc, char **argv)
{
	t_argvs argvs;

	if (!parse_argv(argc, argv, &argvs))
	{
		printf("Error: invalid arguments\n");
		return (EXIT_FAILURE);
	}
	printf("number_of_philos: %d\n", argvs.number_of_philo);
	printf("time_to_die: %d\n", argvs.time_to_die);
	printf("time_to_eat: %d\n", argvs.time_to_eat);
	printf("time_to_sleep: %d\n", argvs.time_to_sleep);
	if (argvs.has_must_eat)
		printf("must_eat_count: %d\n", argvs.num_must_eat);
	else
		printf("must_eat_count: (not set)\n");
	return (0);
}
