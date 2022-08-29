/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 15:29:23 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	_printf(int time, int num, char *action)
// {
	
// }

int	gettime(t_timeval start)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return (int)((double)((now.tv_sec - start.tv_sec) * 1000)
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
	printf("%d : Philosopher %d is \x1b[31mDĘÃD\x1b[0m\n",
		gettime(start), 0);
}
