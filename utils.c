#include "philo.h"

int	is_dead(double time, double time_to_die)
{
	return (time >= time_to_die);
}

double	gettime(t_timeval start, t_timeval now)
{
	return ((double)((now.tv_sec - start.tv_sec) * 1000)
		+ ((double)(now.tv_usec - start.tv_usec) / 1000));
}

int	loop(t_timeval start, t_timeval now, double time_to, int die)
{
	double	a;

	a = 0;//gettime(start, now);
	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while (gettime(start, now) < time_to)
	{
		gettimeofday(&now, NULL);
		a = gettime(start, now);
		if (is_dead(gettime(start, now), die))
			return (1);
	}
	return (is_dead(a, die));
}
