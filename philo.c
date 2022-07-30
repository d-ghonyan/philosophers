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

void	*start_routine(void *info)
{
	// ((t_thread_info	*)info);
	t_timeval		start;
	t_timeval		now;

	// info = (t_thread_info *)arg;
	printf("I LIVE");
	gettimeofday(&start, NULL);
	((t_thread_info	*)info)->start = start;
	((t_thread_info	*)info)->last_meal = start;
	while (1)
	{
		eat(info);
		if (((t_thread_info	*)info)->dead)
		{
			printf("FUCK YOU\n");
			return (NULL);
		}
		_sleep(info);
		if (((t_thread_info	*)info)->dead)
		{
			printf("RETURN\n");
			return (NULL);
		}
		think(info);
		if (((t_thread_info	*)info)->dead)
		{
			printf("RETURN\n");
			return (NULL);
		}
		((t_thread_info	*)info)->first = 0;
	}
}

void	init_thread(t_thread_info *threads, int argc,
	char **argv, pthread_mutex_t *m)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
		if (pthread_mutex_init(m + i++, NULL) < 0)
			printf("AAAAAAAH");
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		mutex_init(m, &(threads[i].mutexes), ft_atoi(argv[1]), i);
		threads[i].m = m;
		threads[i].dead = 0;
		threads[i].first = 1;
		threads[i].num = i;
		threads[i].thread_count = ft_atoi(argv[1]);
		threads[i].to_die = ft_atoi(argv[2]);
		threads[i].to_eat = ft_atoi(argv[3]);
		threads[i].to_sleep = ft_atoi(argv[4]);
		threads[i].must_eat = -1;
		threads[i].eat_count = 0;
		if (argc == 6)
			threads[i].must_eat = ft_atoi(argv[5]);
		i++;
	}
}

int	err(t_thread_info *threads, t_mutex *m)
{
	free(threads);
	free(m);
	return (1);
}

int	main(int argc, char **argv)
{
	int				size;
	int				i;
	// void			*hello;
	t_thread_info	*threads;
	t_mutex			*mutexes;

	// hello = NULL;
	if (check_args(argc, argv) < 0)
		return (-1);
	i = 0;
	size = ft_atoi(argv[1]);
	threads = malloc(sizeof (*threads) * size);
	mutexes = malloc(sizeof (*mutexes) * size);
	if (!threads || !mutexes)
		return (err(threads, mutexes));
	init_thread(threads, argc, argv, mutexes);
	i = -1;
	while (++i < size)
		pthread_create((&(threads + i)->id), NULL, &start_routine, threads + i);
	i = -1;
	t_timeval	now;
	while (1)
	{
		printf("%ld\n", threads[0].last_meal.tv_sec);
		gettimeofday(&now, NULL);
		if (i >= size)
			i = -1;
		while (++i < size)
		{
			if (gettime(threads[i].last_meal, now) >= threads[i].to_die)
			{
				printf("FUCK All of this\n");
				return (0);
			}
		}
	}
}

// while (i < size)
// {
// 	pthread_join(((threads + i++)->id), hello);
// 	if (!hello)
// 	{
// 		printf("DEAD\n");
// 		break ;
// 	}
// }
// i = 0;
// while (i < size)
// 	pthread_mutex_destroy(mutexes + i++);