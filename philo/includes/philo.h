/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:45:33 by linliu            #+#    #+#             */
/*   Updated: 2025/07/08 15:45:57 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> //INT_MIN
# include <stdlib.h> //EXIT_FALIURE

typedef struct s_argvs
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
	int	has_must_eat; //0||1
}	t_argvs;

//parse
int	parse_argv(int argc, char **argv, t_argvs *argvs);

#endif
