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

int	lock(int f, int s, pthread_mutex_t *mutexes);
int	unlock(int f, int s, pthread_mutex_t *mutexes);

int	eat(t_thread_info *info)
{
	int			dead;
	t_timeval	now;
	t_timeval	start;

	dead = 0;
	pthread_mutex_lock(info->mutexes[0]);
	pthread_mutex_lock(info->mutexes[1]);
	gettimeofday(&now, NULL);
	gettimeofday(&start, NULL);
	printf("%.3f : Philosopher %d has taken a fork\n",
		gettime(info->start, now), info->num);
	printf("%.3f : Philosopher %d is eating\n",
		gettime(info->start, now), info->num);
	while (1)
	{
		gettimeofday(&now, NULL);
		if (gettime(start, now) >= info->to_eat)
			break ;
		if (gettime(start, now) >= info->to_die)
		{
			printf("%.3f : Philosopher %d is DĘÃD\n", gettime(info->start, now), info->num);
			dead = 1;
			break ;
		}
	}
	pthread_mutex_unlock(info->mutexes[1]);
	pthread_mutex_unlock(info->mutexes[0]);
	return (dead);
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
	}
}

void	think(t_thread_info *info)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is thinking\n",
		gettime(info->start, now), info->num);
}
