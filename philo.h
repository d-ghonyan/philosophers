#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# include "colors.h"

typedef struct	s_thread_info {
	pthread_t	id;
	char		*msg;
} t_thread_info;

int	ft_atoi(char *s);
int	check_args(int argc, char **argv);
#endif