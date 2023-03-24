/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:15:04 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 19:43:01 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_time(t_solve *solve)
{
	struct timeval		t;
	unsigned long long	res;

	(void)solve;
	gettimeofday(&t, NULL);
	res = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (res);
}

void	ft_usleep(t_solve *solve, long ms)
{
	unsigned long	start;

	start = get_time(solve);
	while (get_time(solve) - start < (unsigned long long)ms)
		usleep(ms / 10);
}

void	philo_sleep(t_solve *solve, int philo_id)
{
	pthread_mutex_lock(&solve->lock);
	if (!solve->is_died)
	{
		printf("%llu %d is thinking\n", get_time(solve) - solve->timestamp,
			philo_id);
		printf("%llu %d is sleeping\n", get_time(solve) - solve->timestamp,
			philo_id);
		pthread_mutex_unlock(&solve->lock);
		usleep(solve->time_to_sleep * 1000);
		return ;
	}
	pthread_mutex_unlock(&solve->lock);
}

void	eat(t_solve *solve, int philo_id)
{
	pthread_mutex_lock(&solve->lock);
	if (!solve->is_died)
	{
		pthread_mutex_unlock(&solve->lock);
		pthread_mutex_lock(&solve->lock);
		printf("%llu %d is eating\n", get_time(solve) - solve->timestamp,
			philo_id);
		solve->philosophers[philo_id].is_ates = 1;
		solve->philosophers[philo_id].meals_ates++;
		pthread_mutex_unlock(&solve->lock);
		usleep(solve->time_to_eat * 1000);
		return ;
	}
	pthread_mutex_unlock(&solve->lock);
}
