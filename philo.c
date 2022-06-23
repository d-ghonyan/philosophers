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

void	*start_routine(void *arg)
{
	t_thread_info	*info;
	t_timeval		start;
	t_timeval		now;

	info = arg;
	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while (1)
	{
		if (loop(start, now, info->to_eat, info->to_die) < 0)
			return (NULL);
	}
	printf(RED "IM DEAD" RESET);
	return (NULL);
}

void	init_thread(t_thread_info *thread, int argc,
	char **argv, pthread_mutex_t *m)
{
	thread->mutexes = m;
	thread->thread_count = ft_atoi(argv[1]);
	thread->to_die = ft_atoi(argv[2]);
	thread->to_eat = ft_atoi(argv[3]);
	thread->to_sleep = ft_atoi(argv[4]);
	thread->must_eat = -1;
	thread->eat_count = 0;
	if (argc == 6)
		thread->must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	int				size;
	int				i;
	t_thread_info	*threads;
	pthread_mutex_t	*mutexes;

	if (check_args(argc, argv) < 0)
		return (1);
	i = 0;
	size = ft_atoi(argv[1]);
	threads = malloc(sizeof (*threads) * size);
	mutexes = malloc(sizeof (*mutexes) * size);
	if (!threads || !mutexes)
		return ((-1));
	i = 0;
	while (i < size)
	{
		pthread_mutex_init(&(mutexes[i]), NULL);
		i++;
	}
	i = 0;
	while (i < size)
	{
		init_thread(&(threads[i]), argc, argv, mutexes);
		threads[i].num = i + 1;
		pthread_create(&(threads[i].id), NULL, &start_routine, &(threads[i]));
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_join((threads[i].id), NULL);
		i++;
	}
}
