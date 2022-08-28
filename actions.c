/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 16:54:48 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm(t_timeval *start, t_timeval *meal)
{
	gettimeofday(meal, NULL);
	gettimeofday(start, NULL);
}

double	another_gettime(t_timeval start, t_timeval now)
{
	return ((double)((now.tv_sec - start.tv_sec) * 1000
		+ ((double)(now.tv_usec - start.tv_usec) / 1000)));
}

void	eat(t_thread_info *info)
{
	t_timeval	now;
	t_timeval	start;

	pthread_mutex_lock(info->mutexes[0]);
	gettimeofday(&now, NULL);
	pthread_mutex_lock(info->mutexes[1]);
	gettimeofday(&(info->last_meal), NULL);
	pthread_mutex_lock(&(info->print_mutex));
	printf("%.3f : %d has taken a fork\n",
		another_gettime(info->start, now), info->num);
	printf("%.3f : %d has taken a fork\n",
		gettime(info->start), info->num);
	printf("%.3f : %d is eating\n",
		gettime(info->start), info->num);
	gettimeofday(&(info->last_meal), NULL);
	pthread_mutex_unlock(&(info->print_mutex));
	gettimeofday(&start, NULL);
	gettimeofday(&(info->last_meal), NULL);
	while (gettime(start) < info->to_eat)
		;
	info->eat_count += (info->must_eat != -1);
	pthread_mutex_unlock(info->mutexes[1]);
	pthread_mutex_unlock(info->mutexes[0]);
}

void	_sleep(t_thread_info *info)
{
	t_timeval	start;

	printf("%.3f : %d is sleeping\n",
		gettime(info->start), info->num);
	gettimeofday(&start, NULL);
	while (gettime(start) < info->to_sleep)
		;
}

void	think(t_thread_info *info)
{
	printf("%.3f : %d is thinking\n",
		gettime(info->start), info->num);
}
