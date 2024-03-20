/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:19:29 by mkocaman          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:19 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	mutex_destroy_2(t_data *data, int flag);

int	destroy_all(t_data *data, int flag, int x)
{
	int	i;

	i = x;
	if (x == data->philo_count - 1)
		mutex_destroy_2(data, flag);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		i--;
	}
	i = data->philo_count - 1;
	mutex_destroy(data, i);
	return (1);
}

int	mutex_destroy(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
	free(data->philos);
	return (1);
}

void	mutex_destroy_2(t_data *data, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->last_eat);
	}
	if (flag == 2)
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->last_eat);
		pthread_mutex_destroy(&data->dead_mutex);
	}
	if (flag == 3)
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->last_eat);
		pthread_mutex_destroy(&data->dead_mutex);
		pthread_mutex_destroy(&data->finish_lock);
	}
}

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (result > 2147483647)
		return (-1);
	return ((int) result);
}

void	action_2(t_philo *philo, int flag)
{
	if (flag == 0)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		eat(philo);
		philo->eat_count++;
		pthread_mutex_lock(&philo->data->finish_lock);
	}
	else if (flag == 1)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		sleep_and_think(philo);
		pthread_mutex_lock(&philo->data->dead_mutex);
	}
}
