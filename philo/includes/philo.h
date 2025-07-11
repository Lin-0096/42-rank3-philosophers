/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:45:33 by linliu            #+#    #+#             */
/*   Updated: 2025/07/11 21:10:06 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h> //INT_MIN
# include <stdlib.h> //EXIT_FALIURE
# include <pthread.h>
# include <sys/time.h> //struct timeval
# include <unistd.h> //usleep:suspend thread execution for an interval measured in microseconds

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die; //duration, how long the one can survive after last meal
	int				time_to_eat;// how long does it take to have a meal
	int			time_to_sleep; //how long of sleep time
	int				num_must_eat;
	long			start_time; //get_current_time
	pthread_mutex_t	*fork; //array of mutax
	pthread_mutex_t	print_mutex; //avoid overlap
	int				someone_died;
	pthread_mutex_t	died_mutex; //if more than one thread try to use int some_died, it will cause data race, so use mutex to protect it
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_mealtime; //if (current_time - last_mealtime > time_to_die), die
	pthread_mutex_t	last_mealtime_mutex; //Multiple threads read/write last_mealtime simultaneously, should protect
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

//utils, init t_data, t_philo
void	cleanup_all_mutex_and_free(t_data *data);
long	get_current_time(void);
void	free_and_destroy_forks(t_data *data, int i);
void	destroy_last_mealtime_mutex(t_data *data, int i);
int		check_death(t_data *data);

//parse and init
int		parse_argv(int argc, char **argv, t_data *argvs);
int		init_data(t_data *data);
int		init_philo(t_data *data);

//action
int		start_thread(t_data *data);
//monitor
void	*monitor_routine(void *arg);

//action utils
void	print_status(t_philo *philo, char *msg);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	drop_fork(t_philo *philo);
void	sleeping(t_philo *philo);

#endif
