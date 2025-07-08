/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:17:43 by linliu            #+#    #+#             */
/*   Updated: 2025/07/08 21:56:09 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>


int	main(int argc, char **argv)
{
	t_data argvs;

	if (!parse_argv(argc, argv, &argvs))
	{
		printf("Error: invalid arguments\n");
		return (EXIT_FAILURE);
	}

	//initialize t_data
	//
	return (0);
}
