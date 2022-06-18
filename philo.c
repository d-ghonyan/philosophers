#include "philo.h"

void	*start_routine(void *arg)
{
	printf("IM THREAD NUMBER %d", *(int *)arg);
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) < 0)
		return (1);
	// int			size;
	// int			i;
	// t_thread_info	*threads;
	// //pthread_t	*threads;

	// i = 0;
	// size = ft_atoi(argv[1]);
	// threads = malloc(sizeof (*threads) * size);
	// while (i < size)
	// {
	// 	pthread_create(&(threads[i].id), NULL, &start_routine, &(threads[i].id));
	// 	i++;
	// }
	// //pthread_create(&thread, NULL, &start_routine, "hello");
	// //pthread_create(&thread, NULL, &start_routine, "hello");
	// for (int i = 0; i < size; i++)
	// 	pthread_join(threads[i].id, NULL);
	// printf("MAIN RETURNED");
}