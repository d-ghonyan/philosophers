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

int	helper_error(t_thread_info *threads, t_mutex *m, int i, int j)
{
	int	a;

	a = -1;
	while (++a < i)
		pthread_mutex_destroy(m + a);
	a = -1;
	while (++a < j)
		pthread_mutex_destroy(&(threads[a].print_mutex));
	free(threads);
	free(m);
	return (1);
}

int	init_helper(t_thread_info *info, int i)
{
	if (pthread_mutex_init(&(info->print_mutex), NULL))
		return (1);
	info->rfork = 0;
	info->lfork = 0;
	info->ready = 0;
	info->dead = 0;
	info->num = i;
	info->must_eat = -1;
	info->eat_count = 0;
	return (0);
}

int	init_thread(t_thread_info *threads, int argc, char **argv, t_mutex *m)
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
		if (init_helper(&(threads[i]), i))
			return (helper_error(threads, m, ft_atoi(argv[1]), i));
		threads[i].to_die = ft_atoi(argv[2]);
		threads[i].to_eat = ft_atoi(argv[3]);
		threads[i].to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			threads[i].must_eat = ft_atoi(argv[5]);
	}
	return (0);
}
