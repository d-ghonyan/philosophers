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

int	eat(t_thread_info *info, int to_lock)
{
	int	r_fork;
	int	l_fork;

	if (info->thread_count <= 2)
		return (-1);
	r_fork = info->num - 1;
	l_fork = info->num + 1;
	if (info->num == 1)
		r_fork = info->thread_count;
	else if (info->num == info->thread_count)
		l_fork = 1;
	if (to_lock)
		return (lock(r_fork, l_fork, info->mutexes));
	else
		return (unlock(r_fork, l_fork, info->mutexes));
}

int	lock(int f, int s, pthread_mutex_t *mutexes)
{
	int a = 0;
	int	b = 0;
	a = f;
	b = s;
	if (f > s)
	{
		a = s;
		b = f;
	}
	printf("LOCKING %d %d\n", a, b);
	pthread_mutex_lock(mutexes + a);
	pthread_mutex_lock(mutexes + b);
	// if (a = pthread_mutex_lock(mutexes + f))
	// 	printf("UNLOCK 1%s\n", strerror (a));
	// if (a = pthread_mutex_lock(mutexes + s))
	// 	printf("UNLOCK 1%s\n", strerror (a));
	// return (0);
}

int	unlock(int f, int s, pthread_mutex_t *mutexes)
{
	int a = 0;
	int	b = 0;
	a = f;
	b = s;
	if (f > s)
	{
		a = s;
		b = f;
	}
	printf("UNLOCKING %d %d\n", a, b);
	pthread_mutex_unlock(mutexes + a);
	pthread_mutex_unlock(mutexes + b);
	// printf("UNLOCKING %d %d\n", f, s);
	// if (a = pthread_mutex_unlock(mutexes + f))
	// 	printf("UNLOCK 1%s\n", strerror (a));
	// if (a = pthread_mutex_unlock(mutexes + s))
	// 	printf("UNLOCK 2%s\n", strerror (a));
	// return (pthread_mutex_unlock(mutexes + f) || pthread_mutex_unlock(mutexes + s));
	return (0);
}