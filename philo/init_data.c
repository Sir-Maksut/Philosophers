/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:13:33 by mkocaman          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:10 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	alloc_control(t_data *data, int flag)
{
	if (flag == 0 && !(data->forks))
		return (1);
	if (flag == 1 && !(data->philos))
	{
		free(data->forks);
		return (1);
	}
	return (0);
}

void	fork_assignment(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].right_fork = i;
		if (i == 0)
			data->philos[i].left_fork = data->philo_count - 1;
		else
			data->philos[i].left_fork = i - 1;
		i++;
	}
}

int	philo_value_set(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_all(data, 0, i - 1));
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			return (destroy_all(data, 0, i - 1));
		data->philos[i].data = data;
		data->philos[i].finished = 0;
		i++;
	}
	return (0);
}

int	value_set(t_data *data, char **av)
{
	data->philo_count = ft_atoi(av[1]);
	data->death_time = (long)ft_atoi(av[2]);
	data->eat_time = (long)ft_atoi(av[3]);
	data->sleep_time = (long)ft_atoi(av[4]);
	if (data->philo_count == -1 || data->death_time == -1
		|| data->eat_time == -1 || data->sleep_time == -1)
		return (1);
	if (data->philo_count > 200 || data->death_time < 60
		|| data->sleep_time < 60 || data->eat_time < 60)
		return (1);
	return (0);
}

int	init_data(t_data *data, char **av, int ac)
{
	if (value_set(data, av))
		return (1);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (alloc_control(data, 0))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (alloc_control(data, 1))
		return (1);
	fork_assignment(data);
	if (philo_value_set(data))
		return (1);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (destroy_all(data, 0, data->philo_count - 1));
	if (pthread_mutex_init(&data->last_eat, NULL) != 0)
		return (destroy_all(data, 1, data->philo_count - 1));
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (destroy_all(data, 2, data->philo_count - 1));
	if (pthread_mutex_init(&data->finish_lock, NULL) != 0)
		return (destroy_all(data, 3, data->philo_count - 1));
	return (data->dead = 0, 0);
}
