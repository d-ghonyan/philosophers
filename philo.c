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

	info = (t_thread_info *)arg;
	gettimeofday(&start, NULL);
	info->start = start;
	info->last_meal = start;
	info->ready = 1;
	while (1)
	{
		if (info->must_eat < 0 || info->eat_count != info->must_eat)
		{
			eat(info);
			if (info->dead)
				return (NULL);
			_sleep(info);
			if (info->dead)
				return (NULL);
			think(info);
			if (info->dead)
				return (NULL);
		}
		else if (info->eat_count != info->must_eat)
			return (NULL);
	}
}

int	init_thread(t_thread_info *threads, int argc,
	char **argv, pthread_mutex_t *m)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
		if (pthread_mutex_init(m + i++, NULL) < 0)
			return (errors(threads, m, i));
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		mutex_init(m, &(threads[i].mutexes), ft_atoi(argv[1]), i);
		threads[i].m = m;
		threads[i].rfork = 0;
		threads[i].lfork = 0;
		threads[i].ready = 0;
		threads[i].dead = 0;
		threads[i].num = i;
		threads[i].to_die = ft_atoi(argv[2]);
		threads[i].to_eat = ft_atoi(argv[3]);
		threads[i].to_sleep = ft_atoi(argv[4]);
		threads[i].must_eat = -1;
		threads[i].eat_count = 0;
		if (argc == 6)
			threads[i].must_eat = ft_atoi(argv[5]);
	}
	return (0);
}

int	err(t_thread_info *threads, t_mutex *m)
{
	free(threads);
	free(m);
	return (1);
}

int	loop(int size, t_thread_info *threads, t_mutex *mutexes)
{
	int			i;
	t_timeval	now;

	while (1)
	{
		i = -1;
		while (++i < size)
		{
			gettimeofday(&now, NULL);
			forks(threads, now, i);
			if (threads[i].ready
				&& gettime(threads[i].last_meal, now) >= threads[i].to_die)
			{
				printf("%.3f : Philosopher %d is DĘÃD\n",
					gettime((threads + i)->start, now), (threads + i)->num);
				for (int j = 0; j < size; j++)
					pthread_detach(threads[j].id);
				errors(threads, mutexes, size);
				return (0);
			}
			if (threads[i].eat_count == threads[i].must_eat)
			{
				errors(threads, mutexes, size);
				return (0);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_thread_info	*threads;
	t_mutex			*mutexes;

	// pthread_mutex_init(&mutexes, NULL);
	// printf("%d\n", pthread_mutex_destroy(&mutexes));
	
	// pthread_mutex_destroy(&mutexes);

	if (check_args(argc, argv) < 0)
		return (-1);
	if (ft_atoi(argv[1]) > 1)
	{
		threads = malloc(sizeof (*threads) * ft_atoi(argv[1]));
		mutexes = malloc(sizeof (*mutexes) * ft_atoi(argv[1]));
		if (!threads || !mutexes)
			return (err(threads, mutexes));
		if (init_thread(threads, argc, argv, mutexes))
			return (0);
		i = -1;
		while (++i < ft_atoi(argv[1]))
			pthread_create((&((threads + i)->id)),
				NULL, &start_routine, threads + i);
		if (loop(ft_atoi(argv[1]), threads, mutexes))
			return (0);
	}
	else
		printf("NO ONE EATS SPAGHETTI WITH ONE FORK");
}
