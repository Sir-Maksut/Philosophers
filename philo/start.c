/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:11:44 by mkocaman          #+#    #+#             */
/*   Updated: 2024/01/03 15:11:44 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	fork_actions(t_philo *philo, int flag)
{
	if (flag == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		ft_write(philo->data, "has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		ft_write(philo->data, "has taken a fork\n", philo->id);
	}
	else if (flag == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
}

void	eat(t_philo *philo)
{
	fork_actions(philo, 0);
	pthread_mutex_lock(&philo->lock);
	ft_write(philo->data, "is eating\n", philo->id);
	pthread_mutex_lock(&philo->data->last_eat);
	philo->last_eat = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->last_eat);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_unlock(&philo->lock);
	fork_actions(philo, 1);
}

void	*supervisor(void *arg)
{
	t_philo			*philo;
	unsigned int	time;

	philo = (t_philo *)arg;
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->data->finish_lock);
	while (philo->data->dead == 0 && philo->finished == 0)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->data->last_eat);
		time = get_time() - philo->data->start_time;
		if (time - philo->last_eat >= philo->data->death_time)
			philo_dead(philo);
		pthread_mutex_unlock(&philo->data->last_eat);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->data->dead_mutex);
		pthread_mutex_lock(&philo->data->finish_lock);
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return ((void *)0);
}

void	*action(void *arg)
{
	t_philo		*philo;
	pthread_t	super_visor;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		return (one_philo(philo));
	if (!(philo->id % 2))
		usleep(10000);
	philo->last_eat = get_time() - philo->data->start_time;
	if (pthread_create(&super_visor, NULL, &supervisor, arg) != 0)
		return ((void *)1);
	pthread_mutex_lock(&philo->data->dead_mutex);
	while (philo->data->dead == 0 && philo->finished == 0)
	{
		action_2(philo, 0);
		if (philo->eat_count == philo->data->must_eat_count)
		{
			philo->finished = 1;
			pthread_mutex_unlock(&philo->data->finish_lock);
			break ;
		}
		action_2(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (pthread_join(super_visor, NULL), (void *)0);
}

void	start(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].philo, NULL, &action,
				&data->philos[i]) != 0)
		{
			destroy_all(data, 3, data->philo_count - 1);
			return ;
		}
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
		{
			destroy_all(data, 3, data->philo_count - 1);
			return ;
		}
	}
	destroy_all(data, 3, data->philo_count - 1);
	return ;
}
