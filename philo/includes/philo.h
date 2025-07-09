/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:45:33 by linliu            #+#    #+#             */
/*   Updated: 2025/07/09 23:11:53 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> //INT_MIN
# include <stdlib.h> //EXIT_FALIURE
# include <pthread.h>
# include <sys/time.h> //struct timeval

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die; //duration, how long the one can survive after last meal
	int				time_to_eat;// how long does it take to have a meal
	int				time_to_sleep; //how long of sleep time
	int				num_must_eat;
	long			start_time; //get_current_time
	pthread_mutex_t	*fork; //array of mutax
	pthread_mutex_t	print; //avoid overlap
	t_philo			*philo;
	int				someone_died;
	pthread_mutex_t	died_mutex; //if more than one thread try to use int some_died, it will cause data race, so use mutex to protect it
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

//parse argv to t_data
int	parse_argv(int argc, char **argv, t_data *argvs);

//utils, init t_data, t_philo
void	cleanup_all_mutex_and_free(t_data *data);
long	get_current_time(void);
int		init_data(t_data *data);
int		init_philo(t_data *data);

#endif
