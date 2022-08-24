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

double	gettime(t_timeval start)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return ((double)((now.tv_sec - start.tv_sec) * 1000)
		+ ((double)(now.tv_usec - start.tv_usec) / 1000));
}

int	errors(t_thread_info *threads, t_mutex *mutexes, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		pthread_mutex_destroy(&(threads[j].print_mutex));
		pthread_mutex_destroy(mutexes + j);
	}
	free(threads);
	free(mutexes);
	return (1);
}

int	err(t_thread_info *threads, t_mutex *m)
{
	free(threads);
	free(m);
	return (1);
}

void	one_fork(int to_die)
{
	t_timeval	start;

	gettimeofday(&start, NULL);
	while (gettime(start) <= to_die)
		;
	printf("%.3f : Philosopher %d is \x1b[31mDĘÃD\x1b[0m\n",
		gettime(start), 0);
}
