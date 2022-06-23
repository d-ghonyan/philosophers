#include "philo.h"

// void	thing(double time_now, double time_to)
// {
// 	while (time_now < time_to)
// 	{
// 		gettime()
// 	}
// }

void	eat(pthread_mutex_t *mutexes, t_thread_info *info)
{
	int	f_fork;
	int	s_fork;

	if (info->thread_count <= 1)
		return ;
	if (info->num == 1)
	{
		f_fork = info->thread_count;
		s_fork = info->2;
	}
	else if (info->num == info->thread_count)
	{
		f_fork = info->thread_count - 1;
		s_fork = info->1;
	}
	else
	{
		f_fork = info->num - 1;
		s_fork = info->num + 1;
	}
	lock(f_fork, s_fork, info-mutexes);
}

void	lock(int f, int s, pthread_mutex_t *mutexes)
{
	pthread_mutex_lock(&mutexes[f]);
	pthread_mutex_lock(&mutexes[s]);
}