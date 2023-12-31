/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 17:42:47 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf(RED "Wrong arguments\n" RESET);
		return (-1);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf(BLUE "Arguments must be > 0\n" RESET);
			return (-1);
		}
		else if (!is_numeric(argv[i]))
		{
			printf(MAGENTA "Arguments must be numbers\n" RESET);
			return (-1);
		}
		i++;
	}
	return (0);
}
