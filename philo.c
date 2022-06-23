#include "philo.h"

void	*start_routine(void *arg)
{

	//while ()
	printf("%p\n", &(((t_thread_info *)(arg))->mutex));
	// printf("IM THREAD NUMBER %d", ((t_thread_info *)arg)->id);
	return (NULL);
}

void	init_thread()
{

}

int	main(int argc, char **argv)
{
	int				size;
	int				i;
	t_thread_info	*threads;

	if (check_args(argc, argv) < 0)
		return (1);
	i = 0;
	size = ft_atoi(argv[1]);
	threads = malloc(sizeof (*threads) * size);

	i = 0;
	while (i < size)
	{
		//threads
		pthread_mutex_init(&(threads[i].mutex), NULL);
		pthread_create(&(threads[i].id), NULL, &start_routine, &(threads[i]));
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_join((threads[i].id), NULL);
		i++;
	}
	// printf("MAIN RETURNED");
}