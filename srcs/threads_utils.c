/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:59:45 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/23 01:32:35 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "philo_data.h"
#include "utils.h"
#include <pthread.h>

int	check_die(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->eat_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (ft_gettimeofday() - last_meal >= philo->args.time_die)
		return (-1);
	return (0);
}

int	end_loop(t_monitor *data)
{
	pthread_mutex_lock(&data->loop_mutex);
	data->loop = false;
	pthread_mutex_unlock(&data->loop_mutex);
	return (0);
}
