/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:32:08 by mkocaman          #+#    #+#             */
/*   Updated: 2024/01/20 13:40:45 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philo;
	pthread_mutex_t	lock;
	int				id;
	int				finished;
	int				eat_count;
	int				last_eat;
	int				left_fork;
	int				right_fork;
	long long int	time_to_die;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	long			death_time;
	long			eat_time;
	long			sleep_time;
	int				must_eat_count;
	int				dead;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	dead_mutex;
	t_philo			*philos;
}					t_data;

int				check_arg(char **av);
int				ft_atoi(char *str);
int				init_data(t_data *data, char **av, int ac);
int				mutex_destroy(t_data *data, int i);
void			ft_write(t_data *data, char *str, int id);
long long int	get_time(void);
int				ft_usleep(long time);
void			start(t_data *data);
int				destroy_all(t_data *data, int flag, int x);
void			philo_dead(t_philo *philo);
void			sleep_and_think(t_philo *philo);
void			action_2(t_philo *philo, int flag);
void			eat(t_philo *philo);
void			*one_philo(t_philo *philo);

#endif
