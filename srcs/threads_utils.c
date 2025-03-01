/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:59:45 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/26 19:38:31 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "philo_data.h"
#include "utils.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int	check_die(t_philo *philo, t_monitor *data)
{
	if (philo->first_meal == true)
	{
		if (ft_gettimeofday() - philo->last_meal >= philo->args.time_die)
		{
			end_loop(data);
			secure_print(philo, DIED, ts(data->start_time));
			return (-1);
		}
	}
	else
	{
		if (ft_gettimeofday() - *philo->start_time >= philo->args.time_die)
		{
			end_loop(data);
			secure_print(philo, DIED, ts(data->start_time));
			return (-1);
		}
	}
	return (0);
}

int	end_loop(t_monitor *data)
{
	pthread_mutex_lock(&data->loop_mutex);
	data->loop = END;
	pthread_mutex_unlock(&data->loop_mutex);
	return (0);
}

void	wait_start(t_philo *philo)
{
	pthread_mutex_lock(philo->loop_mutex);
	while (*philo->loop == WAIT)
		pthread_mutex_unlock_lock(philo->loop_mutex);
	pthread_mutex_unlock(philo->loop_mutex);
}

void	pthread_mutex_unlock_lock(pthread_mutex_t *mtx)
{
	pthread_mutex_unlock(mtx);
	pthread_mutex_lock(mtx);
}

int	secure_print(t_philo *philo, t_state mod, size_t time)
{
	int	ret;

	ret = 0;
	if (mod == DIED)
		printf("%zu %zu died\n", time, philo->nb);
	if (mod == DIED)
		return (ret);
	pthread_mutex_lock(philo->loop_mutex);
	if (*philo->loop == END || *philo->loop == ERROR)
		ret = -1;
	else if (mod == EAT)
		printf("%zu %zu is eating\n", time, philo->nb);
	else if (mod == THINK)
		printf("%zu %zu is thinking\n", time, philo->nb);
	else if (mod == SLEEP)
		printf("%zu %zu is sleeping\n", time, philo->nb);
	else if (mod == FORK)
		printf("%zu %zu has taken a fork\n", time, philo->nb);
	pthread_mutex_unlock(philo->loop_mutex);
	return (ret);
}
