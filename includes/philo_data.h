/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:05:35 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/19 19:25:31 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <sys/types.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct	s_fork
{
	size_t	nb;
	pthread_mutex_t	mutex;
	bool			available;
}				t_fork;

typedef struct	s_args
{
	size_t	time_eat;
	size_t	time_die;
	size_t	time_sleep;
	size_t	max_meal;
	bool	meal_limit;
}				t_args;

typedef struct	s_philo
{
	pthread_t		*thread;
	size_t			nb;
	t_args			args;
	t_fork			*r_fork;
	t_fork			*l_fork;
	size_t			last_meal;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*loop_mutex;
	bool			*loop;
}				t_philo;

typedef struct	s_monitor
{
	size_t			start_time;
	size_t			nb_philos;
	t_args			args;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	loop_mutex;
	bool			loop;
}				t_monitor;

#endif
