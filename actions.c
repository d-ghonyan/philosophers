/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 13:00:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// gettimeofday(&now, NULL);
// if (gettime(info->last_meal, now) >= info->to_die)
// {
// 	printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
// 	info->dead = 1;
// 	return ;
// }
// printf("%.3f : Philosopher %d has taken the first fork\n",
// 	gettime(info->start, now), info->num);

void	eat(t_thread_info *info)
{
	t_timeval	now;
	t_timeval	start;

	if (gettime(info->last_meal, now) >= info->to_die)
	{
		printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
		info->dead = 1;
		return ;
	}
	pthread_mutex_lock(info->mutexes[0]);
	if (gettime(info->last_meal, now) >= info->to_die)
	{
		printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
		info->dead = 1;
		return ;
	}
	pthread_mutex_lock(info->mutexes[1]);
	gettimeofday(&now, NULL);
	if (gettime(info->start, now) >= info->to_die && info->first)
	{
		printf("%.3f : Philosopher %d is DĘÃD\n",
			gettime(info->start, now), info->num);
		info->dead = 1;
		return ;
	}
	if (gettime(info->last_meal, now) >= info->to_die)
	{
		printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
		info->dead = 1;
		return ;
	}
	gettimeofday(&start, NULL);
	printf("%.3f : Philosopher %d is eating\n",
		gettime(info->start, now), info->num);
	info->last_meal = now;
	while (1)
	{
		gettimeofday(&now, NULL);
		if (gettime(start, now) >= info->to_eat)
			break ;
		if (gettime(info->last_meal, now) >= info->to_die)
		{
			printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
			info->dead = 1;
			break ;
		}
	}
	pthread_mutex_unlock(info->mutexes[1]);
	pthread_mutex_unlock(info->mutexes[0]);
}

void	_sleep(t_thread_info *info)
{
	t_timeval	now;
	t_timeval	start;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is sleeping\n",
		gettime(info->start, now), info->num);
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if (gettime(start, now) >= info->to_sleep)
			break ;
		if (gettime(info->last_meal, now) >= info->to_die)
		{
			printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
			info->dead = 1;
			break ;
		}
	}
}

void	think(t_thread_info *info)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is thinking\n",
		gettime(info->start, now), info->num);
	if (gettime(info->last_meal, now) >= info->to_die)
	{
		printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
		info->dead = 1;
	}
}
