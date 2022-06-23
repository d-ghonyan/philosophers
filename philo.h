#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

typedef struct	s_thread_info {
	int				num;
	int				to_eat;
	int				to_die;
	int				to_sleep;
	int				must_eat;
	time_t			time;
	pthread_t		id;
	pthread_mutex_t	mutex;
} t_thread_info;

int	ft_atoi(char *s);
int	check_args(int argc, char **argv);
#endif