/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:01:23 by mkocaman          #+#    #+#             */
/*   Updated: 2023/12/31 00:01:23 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (long long int)1000) + (tv.tv_usec / 1000));
}

void	ft_write(t_data *data, char *str, int id)
{
	int	time;

	pthread_mutex_lock(&data->write);
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead == 0)
	{
		time = get_time() - data->start_time;
		printf("%d : %d %s", time, id, str);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->write);
}

int	ft_usleep(long time)
{
	long long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	philo_dead(t_philo *philo)
{
	unsigned int	dead_time;

	pthread_mutex_unlock(&philo->data->last_eat);
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead == 0)
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		dead_time = get_time() - philo->data->start_time;
		printf("%u : %d is died\n", dead_time, philo->id);
		pthread_mutex_lock(&philo->data->dead_mutex);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_lock(&philo->data->last_eat);
}

void	sleep_and_think(t_philo *philo)
{
	ft_write(philo->data, "is sleeping\n", philo->id);
	ft_usleep(philo->data->sleep_time);
	ft_write(philo->data, "is thinking\n", philo->id);
}
