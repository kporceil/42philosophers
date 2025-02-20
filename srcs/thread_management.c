/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:25:39 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/17 15:21:33 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_data.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	philo_routine(t_philo *philo);
void	philo_eat(t_philo *philo);

int	starting_threads(t_monitor *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	pthread_mutex_lock(&data->loop_mutex);
	while(i < data->nb_philos)
	{
		pthread_create(philo[i].thread, NULL, philo_routine, philo + i);
		++i;
	}
	data->start_time = ft_gettimeofday();
	data->loop = true;
	pthread_mutex_unlock(&data->loop_mutex);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	if (philo->nb % 2)
		usleep(philo->args.time_eat >> 1);
	pthread_mutex_lock(philo->loop_mutex);
	while (*philo->loop)
	{
		pthread_mutex_unlock(philo->loop_mutex);
		philo_eat(philo);
		printf("%zu %zu is sleeping\n", ts(*philo->start_time), philo->nb);
		usleep(philo->args.time_sleep);
		printf("%zu %zu is thinking\n", ts(*philo->start_time), philo->nb);
		pthread_mutex_lock(philo->loop_mutex);
	}
	pthread_mutex_unlock(philo->loop_mutex);
}

void	philo_eat(t_philo *philo)
{
	size_t	i;
	t_fork	*fork;

	i = 0;
	if (philo->nb % 2)
		fork = philo->r_fork;
	else
		fork = philo->l_fork;
	while (i++ < 2)
	{
		pthread_mutex_lock(&fork->mutex);
		while (fork->available == false)
		{
			pthread_mutex_unlock(&fork->mutex);
			pthread_mutex_lock(&fork->mutex);
		}
		fork->available = false;
		pthread_mutex_unlock(&fork->mutex);
		printf("%zu %zu has taken a fork\n", ts(*philo->start_time), philo->nb);
		fork = philo->r_fork;
		if (philo->nb % 2)
			fork = philo->l_fork;
	}
	printf("%zu %zu is eating\n", ts(*philo->start_time), philo->nb);
	usleep(philo->args.time_eat);
}
