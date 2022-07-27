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

void	mutex_init(t_mutex *m, t_mutex *(*mutexes)[2], int count, int n)
{
	if (n)
	{
		(*mutexes)[1] = m + n;
		if (n)
			(*mutexes)[0] = m + (n - 1);
		else
			(*mutexes)[0] = m + (count - 1);
	}
	else
	{
		(*mutexes)[0] = m + n;
		if (n)
			(*mutexes)[1] = m + (n - 1);
		else
			(*mutexes)[1] = m + (count - 1);
	}
}
