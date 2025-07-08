/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:45:33 by linliu            #+#    #+#             */
/*   Updated: 2025/07/08 21:38:45 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> //INT_MIN
# include <stdlib.h> //EXIT_FALIURE
# include <pthread.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;

	long			start_time;
	pthread_mutex_t	*fork; //array of mutax
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_mealtime;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;


//parse
int	parse_argv(int argc, char **argv, t_data *argvs);

#endif
