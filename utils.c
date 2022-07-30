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

double	gettime(t_timeval start, t_timeval now)
{
	return ((double)((now.tv_sec - start.tv_sec) * 1000)
		+ ((double)(now.tv_usec - start.tv_usec) / 1000));
}

int	errors(t_thread_info *threads, t_mutex *mutexes, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		pthread_mutex_destroy(mutexes + j);
	free(threads);
	free(mutexes);
	return (1);
}

void	forks(t_thread_info *threads, t_timeval now, int i)
{
	if (threads[i].rfork)
	{
		(threads + i)->rfork = 0;
		printf("%.3f : Philosopher %d has taken a fork\n",
			gettime((threads + i)->start, now), threads[i].num);
	}
	else if (threads[i].lfork)
	{
		(threads + i)->lfork = 0;
		printf("%.3f : Philosopher %d has taken a fork\n",
			gettime((threads + i)->start, now), threads[i].num);
	}
}
