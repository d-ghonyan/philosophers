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

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	mutex_init(t_mutex *m, t_mutex *(*mutexes)[2], int count, int n)
{
	int	first;
	int	second;

	first = 0;
	second = 1;
	if (n == count - 1)
		ft_swap(&first, &second);
	(*mutexes)[first] = m + n;
	if (n == count - 1)
		(*mutexes)[second] = m + 0;
	else
		(*mutexes)[second] = m + n + 1;
}
