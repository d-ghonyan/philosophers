#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

typedef struct s_thread_info {
	int				num;
	int				thread_count;
	int				to_eat;
	int				to_die;
	int				to_sleep;
	int				must_eat;
	int				eat_count;
	time_t			time;
	pthread_t		id;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*mutexes;
}	t_thread_info;

typedef struct timeval	t_timeval;

int		ft_atoi(char *s);
int		check_args(int argc, char **argv);
int		loop(t_timeval start, t_timeval now, double time_to, int die);
double	gettime(struct timeval start, struct timeval now);

#endif