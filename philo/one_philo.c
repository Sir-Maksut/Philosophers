/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:50 by mkocaman          #+#    #+#             */
/*   Updated: 2024/01/20 13:41:57 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	printf("0 : 1 has taken a fork\n");
	ft_usleep(philo->data->death_time);
	printf("%ld : 1 is died\n", philo->data->death_time);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return ((void *)1);
}
