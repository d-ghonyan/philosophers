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

	int barev = 0;
	info = arg;
	//pthread_mutex_lock(info->mutexes);
	printf("Thread %d is ", info->num);
	eat(info, 1);

	barev += 15;
	//printf("%d\n", barev);
	// while (1)
	// {
	// 	eat(info, 1);
	// 	printf("LOCKED\n");
	printf("HJELLOOOOA[PDASD] %d\n", info->num);
	// 	if (loop(start, now, info->to_eat, info->to_die))
	// 		return (NULL);
	// 	printf("BACK FROM LOOP");
	// 	eat(info, 0);
	// 	printf("UNLOCKED\n");
	// }
	//eat(info);
	//printf(RED "IM DEAD" RESET);
	//pthread_mutex_unlock((info->mutexes));
	printf("Thread %d is ", info->num);
	//eat(info, 0);
	eat(info, 0);
	return (NULL);
}

void	init_thread(t_thread_info *threads, int argc,
	char **argv, pthread_mutex_t *m)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		mutex_init(m, &(threads[i].mutexes), ft_atoi(argv[1]), i);
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

int	main(int argc, char **argv)
{
	int				size;
	int				i;
	t_thread_info	*threads;
	t_mutex			*mutexes;

	if (check_args(argc, argv) < 0)
		return (1);
	i = 0;
	size = ft_atoi(argv[1]);
	threads = malloc(sizeof (*threads) * size);
	mutexes = malloc(sizeof (*mutexes) * size);
	if (!threads || !mutexes)
	{
		free(threads);
		free(mutexes);
		return (-1);
	}
	i = 0;
	while (i < size)
	{
		pthread_mutex_init(mutexes + i, NULL);
		i++;
	}
	init_thread(threads, argc, argv, mutexes);
	pthread_mutex_lock(threads[0].mutexes[0]);
	i = 0;
	// while (i < size)
	// {
	// 	init_thread(&(threads[i]), argc, argv, NULL);
	// 	threads[i].num = i + 1;
	// 	// threads[i].mutexes = mutexes;
	// 	pthread_create(&(threads[i].id), NULL, &start_routine, &(threads[i]));
	// 	i++;
	// }
	// i = 0;
	// while (i < size)
	// {
	// 	pthread_join((threads[i].id), NULL);
	// 	i++;
	// }
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(mutexes + i);
		i++;
	}
}
