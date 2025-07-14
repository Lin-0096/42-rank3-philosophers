/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:59:20 by linliu            #+#    #+#             */
/*   Updated: 2025/07/14 17:31:28 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id == philo->data->number_of_philo)
	{
		//pick up in reverse order
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		//pick up the left one first and right one then
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	long	start;

	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_mealtime = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	//do not sleep till end, should sleep a little while and check death
	start = get_current_time();
	while (get_current_time() - start < philo->data->time_to_eat)
	{
		if (check_stop(philo->data))
			break ;
		usleep(500);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	long	start;

	print_status(philo, "is sleeping");
	start = get_current_time();
	//do not sleep till end, should sleep a little while and check death
	while (get_current_time() - start < philo->data->time_to_sleep)
	{
		if (check_stop(philo->data))
			break ;
		usleep(500);
	}
}
