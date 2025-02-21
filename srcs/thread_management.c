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
int	philo_eat(t_philo *philo);

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
	pthread_mutex_lock(philo->loop_mutex);
	if (philo->nb % 2)
		usleep(philo->args.time_eat >> 1);
	while (*philo->loop)
	{
		pthread_mutex_unlock(philo->loop_mutex);
		if (philo_eat(philo) != 0)
			return ;
		if (secure_print(philo, SLEEP) != 0)
			return ;
		usleep(philo->args.time_sleep);
		if (secure_print(philo, THINK) != 0)
			return ;
		pthread_mutex_lock(philo->loop_mutex);
	}
	pthread_mutex_unlock(philo->loop_mutex);
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
			pthread_mutex_unlock_lock(&fork->mutex);
		fork->available = false;
		pthread_mutex_unlock(&fork->mutex);
		if (secure_print(philo, FORK) != 0)
			return (-1);
		fork = philo->r_fork;
		if (philo->nb % 2)
			fork = philo->l_fork;
	}
	if (secure_print(philo, EAT) != 0)
		return (-1);
	update_last_meal(philo, ft_gettimeofday());
	usleep(philo->args.time_eat);
	return (0);
}
