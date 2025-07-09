/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:45:33 by linliu            #+#    #+#             */
/*   Updated: 2025/07/09 16:42:30 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> //INT_MIN
# include <stdlib.h> //EXIT_FALIURE
# include <pthread.h>
# include <sys/time.h> //struct timeval
/*
struct timeval {
    time_t      tv_sec; // seconds(start from 1.1.1970从1970)
    suseconds_t tv_usec;//microseconds(0 ~ 999999)
};
*/
typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die; //duration, how long the one can survive after last meal
	int				time_to_eat;// how long does it take to have a meal
	int				time_to_sleep; //how long of sleep time
	int				num_must_eat;

	long			start_time;
	pthread_mutex_t	*fork; //array of mutax
	pthread_mutex_t	print; //avoid overlap
	t_philo			*philo;

	int				someone_died; //???do i need this
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_mealtime; //if (current_time - last_mealtime > time_to_die), die
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

//parse
int	parse_argv(int argc, char **argv, t_data *argvs);

//utils
void	cleanup_init_philo_fail(t_data *data);
long	get_current_time(void);
int		init_data(t_data *data);
int		init_philo(t_data *data);

#endif
