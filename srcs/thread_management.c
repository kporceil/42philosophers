/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:25:39 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/26 20:21:09 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "philo_data.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int	starting_threads(t_monitor *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	pthread_mutex_lock(&data->loop_mutex);
	while (i < data->nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, philo + i))
		{
			data->loop = ERROR;
			pthread_mutex_unlock(&data->loop_mutex);
			while (i--)
				pthread_join(philo[i].thread, NULL);
			return (-1);
		}
		++i;
	}
	data->loop = LOOP;
	data->start_time = ft_gettimeofday();
	pthread_mutex_unlock(&data->loop_mutex);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = args;
	wait_start(philo);
	if (secure_print(philo, THINK) != 0)
		return (NULL);
	if (philo->nb % 2)
		usleep((philo->args.time_eat * 1000) >> 1);
	while (1)
	{
		if (philo_eat(philo) != 0)
			return (NULL);
		if (secure_print(philo, EAT) != 0)
			return (free_fork(philo, 0), NULL);
		update_last_meal(philo, ft_gettimeofday());
		usleep(philo->args.time_eat * 1000);
		(void)free_fork(philo, 0);
		if (secure_print(philo, SLEEP) != 0)
			return (NULL);
		usleep(philo->args.time_sleep * 1000);
		if (secure_print(philo, THINK) != 0)
			return (NULL);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	size_t	i;
	t_fork	*fork;

	i = 0;
	fork = philo->l_fork;
	if (philo->nb % 2)
		fork = philo->r_fork;
	while (i++ < 2)
	{
		take_fork(fork);
		philo->fork_taken[i - 1] = fork;
		if (secure_print(philo, FORK) != 0)
			return (free_fork(philo, -1));
		fork = philo->r_fork;
		if (philo->nb % 2)
			fork = philo->l_fork;
		if (philo->l_fork == philo->r_fork)
			return (-1);
	}
	return (0);
}

int	monitor_threads(t_monitor *data)
{
	size_t	i;
	size_t	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->philos[i].eat_mutex);
			if (check_die(data->philos + i, data) != 0)
			{
				pthread_mutex_unlock(&data->philos[i].eat_mutex);
				return (0);
			}
			if (data->args.meal_limit)
				if (check_meal_limit(data->philos + i) == true)
					++count;
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
			++i;
		}
		if (count >= data->nb_philos)
			return (end_loop(data));
		usleep((data->args.time_die >> 2) * 1000);
	}
}

int	end_thread(t_monitor *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philos)
		pthread_join(data->philos[i++].thread, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->philos[i].eat_mutex);
		pthread_mutex_destroy(&data->forks[i++].mutex);
	}
	pthread_mutex_destroy(&data->loop_mutex);
	return (0);
}
