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

void	norm(t_timeval *now, t_timeval *start, t_timeval *meal)
{
	gettimeofday(meal, NULL);
	gettimeofday(now, NULL);
	gettimeofday(start, NULL);
}

int	norm_again(t_thread_info *info, t_timeval now)
{
	if (gettime(info->last_meal, now) >= info->to_die)
	{
		info->dead = 1;
		*(info->one_dead) = 1;
		return (1);
	}
	return (0);
}

// void	eat(t_thread_info *info)
// {
// 	t_timeval	now;
// 	t_timeval	start;

// 	if (*(info->one_dead))
// 		return ;
// 	pthread_mutex_lock(info->mutexes[0]);
// 	info->rfork = 1;
// 	pthread_mutex_lock(info->mutexes[1]);
// 	info->lfork = 1;
// 	norm(&now, &start, &(info->last_meal));
// 	if (*(info->one_dead))
// 		return ;
// 	printf("%.3f : Philosopher %d is eating\n",
// 		gettime(info->start, now), info->num);
// 	while (gettime(start, now) < info->to_eat && !(*(info->one_dead)))
// 		gettimeofday(&now, NULL);
// 	pthread_mutex_unlock(info->mutexes[1]);
// 	info->lfork = 0;
// 	pthread_mutex_unlock(info->mutexes[0]);
// 	info->rfork = 0;
// 	info->eat_count += (info->must_eat != -1);
// }

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
		if (gettime(start, now) >= info->to_sleep || *(info->one_dead))
			break ;
		// if (gettime(info->last_meal, now) >= info->to_die)
		// {
		// 	info->dead = 1;
		// 	*(info->one_dead) = 1;
		// 	break ;
		// }
	}
}

void	think(t_thread_info *info)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	printf("%.3f : Philosopher %d is thinking\n",
		gettime(info->start, now), info->num);
}
