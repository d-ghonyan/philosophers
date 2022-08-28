/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 17:03:40 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*s(void *arg)
{
	t_thread_info	*info;

	info = (t_thread_info *)arg;
	gettimeofday(&(info->last_meal), NULL);
	if (info->num % 2 == 0)
		usleep(15000);
	info->ready = 1;
	while (1)
	{
		eat(info);
		_sleep(info);
		think(info);
	}
}

int	im_tired(t_thread_info *threads, int size)
{
	int			i;
	static int	hello = 0;

	i = -1;
	if (hello)
		return (1);
	if (threads[0].must_eat == -1)
		return (0);
	while (++i < size)
	{
		if (threads[i].eat_count < threads[i].must_eat)
			return (0);
	}
	hello = 1;
	return (1);
}

int	print(t_thread_info *threads, int i)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(threads[i].print_mutex));
	if (gettime(threads[i].last_meal) <= threads[i].to_die)
	{
		pthread_mutex_unlock(&(threads[i].print_mutex));
		return (1);
	}
	printf("%.3f : Philosopher %d is \x1b[31mDĘÃD\x1b[0m\n",
		gettime((threads + i)->start), (threads + i)->num);
	pthread_mutex_unlock(&(threads[i].print_mutex));
	return (0);
}

int	loop(int size, t_thread_info *threads, t_mutex *mutexes)
{
	int			i;
	int			a;

	while (1)
	{
		i = -1;
		while (++i < size)
		{
			if ((threads[i].ready
					&& gettime(threads[i].last_meal) > threads[i].to_die)
				|| im_tired(threads, size))
			{
				if (!im_tired(threads, size))
					if (print(threads, i))
						continue ;
				if (gettime(threads[i].last_meal) <= threads[i].to_die
					&& !im_tired(threads, size))
					continue ;
				a = -1;
				while (++a < size)
					pthread_detach(threads[a].id);
				return (errors(threads, mutexes, size));
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_timeval		start;
	int				i;
	t_thread_info	*threads;
	t_mutex			*mutexes;

	if (check_args(argc, argv) < 0)
		return (1);
	if (ft_atoi(argv[1]) > 1)
	{
		threads = malloc(sizeof (*threads) * ft_atoi(argv[1]));
		mutexes = malloc(sizeof (*mutexes) * ft_atoi(argv[1]));
		if (!threads || !mutexes)
			return (err(threads, mutexes));
		if (init_thread(threads, argc, argv, mutexes))
			return (0);
		i = -1;
		gettimeofday(&start, NULL);
		while (++i < ft_atoi(argv[1]))
		{
			threads[i].start = start;
			pthread_create((&((threads + i)->id)), NULL, &s, threads + i);
		}
		return (loop(ft_atoi(argv[1]), threads, mutexes));
	}
	one_fork(ft_atoi(argv[2]));
}
