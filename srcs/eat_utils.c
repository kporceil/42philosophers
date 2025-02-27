/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:12:45 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/26 19:32:14 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "utils.h"
#include "philo_data.h"
#include <pthread.h>
#include <stdbool.h>

int	free_fork(t_philo *philo, int ret)
{
	size_t	i;

	i = 0;
	while (i++ < 2)
	{
		if (philo->fork_taken[i - 1] == NULL)
			continue ;
		pthread_mutex_lock(&philo->fork_taken[i - 1]->mutex);
		philo->fork_taken[i - 1]->available = true;
		pthread_mutex_unlock(&philo->fork_taken[i - 1]->mutex);
		philo->fork_taken[i - 1] = NULL;
	}
	return (ret);
}

void	update_last_meal(t_philo *philo, size_t time)
{
	pthread_mutex_lock(&philo->eat_mutex);
	++philo->nb_meal;
	philo->last_meal = time;
	philo->first_meal = true;
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	while (fork->available == false)
		pthread_mutex_unlock_lock(&fork->mutex);
	fork->available = false;
	pthread_mutex_unlock(&fork->mutex);
}

bool	check_meal_limit(t_philo *philo)
{
	if (philo->nb_meal >= philo->args.max_meal)
		return (true);
	return (false);
}
