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

void	init_helper(t_thread_info *info, int *one_dead, int i)
{
	info->one_dead = one_dead;
	info->rfork = 0;
	info->lfork = 0;
	info->ready = 0;
	info->dead = 0;
	info->num = i;
	info->must_eat = -1;
	info->eat_count = 0;
}

int	init_thread(t_thread_info *threads, int argc, char **argv, t_mutex *m)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
		if (pthread_mutex_init(m + i++, NULL) < 0)
			return (errors(threads, m, i));
	i = -1;
	*(threads[0].one_dead) = 0;
	while (++i < ft_atoi(argv[1]))
	{
		mutex_init(m, &(threads[i].mutexes), ft_atoi(argv[1]), i);
		init_helper(&(threads[i]), threads[0].one_dead, i);
		threads[i].to_die = ft_atoi(argv[2]);
		threads[i].to_eat = ft_atoi(argv[3]);
		threads[i].to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			threads[i].must_eat = ft_atoi(argv[5]);
	}
	return (0);
}
