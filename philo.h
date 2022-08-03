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

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;

typedef struct thread_info {
	int				rfork;
	int				lfork;
	int				ready;
	int				dead;
	int				num;
	int				to_eat;
	int				to_die;
	int				to_sleep;
	int				must_eat;
	int				eat_count;
	int				*one_dead;
	time_t			time;
	pthread_t		id;
	t_timeval		start;
	t_timeval		last_meal;
	pthread_mutex_t	*(mutexes)[2];
}	t_thread_info;

int		ft_atoi(char *s);
int		check_args(int argc, char **argv);
int		errors(t_thread_info *threads, t_mutex *mutexes, int i);
void	eat(t_thread_info *info);
void	_sleep(t_thread_info *info);
void	think(t_thread_info *info);
void	still_norm(t_thread_info *threads, t_mutex *mutexes, int size, int i);
void	mutex_init(t_mutex *m, t_mutex *(*mutexes)[2], int count, int n);
void	forks(t_thread_info *threads, t_timeval now, int i);
double	gettime(struct timeval start, struct timeval now);

#endif