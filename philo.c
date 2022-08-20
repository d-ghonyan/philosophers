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

	info = (t_thread_info *)arg;
	gettimeofday(&(info->last_meal), NULL);
	gettimeofday(&(info->start), NULL);
	info->ready = 1;
	while (1)
	{
		if (info->must_eat < 0 || info->eat_count != info->must_eat)
		{
			eat(info);
			if (*(info->one_dead))
				return (NULL);
			_sleep(info);
			if (*(info->one_dead))
				return (NULL);
			think(info);
			if (*(info->one_dead))
				return (NULL);
		}
		else if (info->eat_count == info->must_eat)
			return (NULL);
	}
}

int	loop(int size, t_thread_info *threads, t_mutex *mutexes)
{
	int			i;
	int			a;
	t_timeval	now;

	a = -1;
	while (1)
	{
		i = -1;
		while (++i < size)
		{
			gettimeofday(&now, NULL);
			forks(threads, now, i);
			if ((threads[i].ready
				&& gettime(threads[i].last_meal, now) >= threads[i].to_die)
				|| threads[i].eat_count == threads[i].must_eat)
			{
				gettimeofday(&now, NULL);
				if (threads[i].eat_count != threads[i].must_eat)
				{
					printf("%.3f : Philosopher %d is DĘÃD\n",
						gettime((threads + i)->start, now), (threads + i)->num);
				}
				*(threads[i].one_dead) = 1;
				while (++a < size)
					pthread_join(threads[a].id, NULL);
				errors(threads, mutexes, size);
				return (1);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int				i;
	int				one_dead;
	t_thread_info	*threads;
	t_mutex			*mutexes;

	if (check_args(argc, argv) < 0)
		return (-1);
	if (ft_atoi(argv[1]) > 1)
	{
		threads = malloc(sizeof (*threads) * ft_atoi(argv[1]));
		mutexes = malloc(sizeof (*mutexes) * ft_atoi(argv[1]));
		if (!threads || !mutexes)
			return (err(threads, mutexes));
		threads[0].one_dead = &one_dead;
		if (init_thread(threads, argc, argv, mutexes))
			return (0);
		i = -1;
		while (++i < ft_atoi(argv[1]))
			pthread_create((&((threads + i)->id)),
				NULL, &start_routine, threads + i);
		if (loop(ft_atoi(argv[1]), threads, mutexes))
			return (0);
	}
	printf("NO ONE EATS SPAGHETTI WITH ONE FORK\n");
}
