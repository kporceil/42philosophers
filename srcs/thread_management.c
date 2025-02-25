/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:25:39 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/23 01:44:18 by kporceil         ###   ########lyon.fr   */
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
	data->start_time = ft_gettimeofday();
	while(i < data->nb_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&philo[i].thread, NULL, philo_routine, philo + i) != 0)
			while(i--)
				pthread_join(philo[i].thread, NULL);
		++i;
	}
	data->loop = true;
	pthread_mutex_unlock(&data->loop_mutex);
	return (0);
}

void	free_fork(t_philo *philo)
{
	size_t	i;
	t_fork	*fork;

	i = 0;
	fork = philo->l_fork;
	if (philo->nb % 2)
		fork = philo->r_fork;
	while (i++ < 2)
	{
		pthread_mutex_lock(&fork->mutex);
		fork->available = true;
		pthread_mutex_unlock(&fork->mutex);
		fork = philo->r_fork;
		if (philo->nb % 2)
			fork = philo->l_fork;
	}
}

void	*philo_routine(void *args)
{
	t_philo	*philo;
	bool	loop;

	philo = args;
	pthread_mutex_lock(philo->loop_mutex);
	loop = *philo->loop;
	pthread_mutex_unlock(philo->loop_mutex);
	secure_print(philo, THINK);
	if (philo->nb % 2)
	{
		usleep(philo->args.time_eat >> 1);
		pthread_mutex_lock(philo->loop_mutex);
		loop = *philo->loop;
		pthread_mutex_unlock(philo->loop_mutex);
	}
	while (loop)
	{
		if (philo_eat(philo) != 0)
			return (NULL);
		free_fork(philo);
		if (secure_print(philo, SLEEP) != 0)
			return (NULL);
		usleep(philo->args.time_sleep * 1000);
		if (secure_print(philo, THINK) != 0)
			return (NULL);
		pthread_mutex_lock(philo->loop_mutex);
		loop = *philo->loop;
		pthread_mutex_unlock(philo->loop_mutex);
	}
	return (NULL);
}

void	update_last_meal(t_philo *philo, size_t time)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->eat_mutex);
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
		pthread_mutex_lock(&fork->mutex);
		while (fork->available == false)
		{
			pthread_mutex_unlock_lock(&fork->mutex);
			pthread_mutex_lock(philo->loop_mutex);
			if (!*philo->loop)
			{
				pthread_mutex_unlock(&fork->mutex);
				pthread_mutex_unlock(philo->loop_mutex);
				return (-1);
			}
			pthread_mutex_unlock(philo->loop_mutex);
		}
		fork->available = false;
		pthread_mutex_unlock(&fork->mutex);
		if (secure_print(philo, FORK) != 0)
			return (-1);
		fork = philo->r_fork;
		if (philo->nb % 2)
			fork = philo->l_fork;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	++philo->nb_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (secure_print(philo, EAT) != 0)
		return (-1);
	update_last_meal(philo, ft_gettimeofday());
	usleep(philo->args.time_eat * 1000);
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
			if (check_die(data->philos + i) != 0)
			{
				end_loop(data);
				secure_print(data->philos + i, DIED);
				return (0);
			}
			if (data->args.meal_limit)
			{
				pthread_mutex_lock(&data->philos[i].meal_mutex);
				if (data->philos[i].nb_meal >= data->args.max_meal)
					++count;
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
			}
			++i;
		}
		if (count >= data->nb_philos)
			return (end_loop(data));
	}
}

int	end_thread(t_monitor *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].eat_mutex);
		pthread_mutex_destroy(&data->forks[i].mutex);
		++i;
	}
	return (0);
}
