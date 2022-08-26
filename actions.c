/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 12:26:05 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm(t_timeval *now, t_timeval *start, t_timeval *meal)
{
	gettimeofday(meal, NULL);
	gettimeofday(now, NULL);
	gettimeofday(start, NULL);
}

void	eat(t_thread_info *info)
{
	t_timeval	now;
	t_timeval	start;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(info->mutexes[0]);
	printf("%.3f : Philosopher %d has taken right fork\n",
		gettime(info->start), info->num);
	pthread_mutex_lock(info->mutexes[1]);
	printf("%.3f : Philosopher %d has taken left fork\n",
		gettime(info->start), info->num);
	norm(&now, &start, &(info->last_meal));
	pthread_mutex_lock(&(info->print_mutex));
	printf("%.3f : Philosopher %d is \x1b[32meating\x1b[0m\n",
		gettime(info->start), info->num);
	pthread_mutex_unlock(&(info->print_mutex));
	while (gettime(start) < info->to_eat)
		gettimeofday(&now, NULL);
	info->eat_count += (info->must_eat != -1);
	pthread_mutex_unlock(info->mutexes[1]);
	pthread_mutex_unlock(info->mutexes[0]);
}

void	_sleep(t_thread_info *info)
{
	t_timeval	now;
	t_timeval	start;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is \x1b[34msleeping\x1b[0m\n",
		gettime(info->start), info->num);
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if (gettime(start) >= info->to_sleep)
			break ;
	}
}

void	think(t_thread_info *info)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is \x1b[35mthinking\x1b[0m\n",
		gettime(info->start), info->num);
}
