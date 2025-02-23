/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:59:43 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/19 19:25:21 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_data.h"
#include "parsing.h"
#include "utils.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


static int	init_forks(t_monitor *data);
static int	init_philos(t_monitor *data);

int	init_args(int argc, char **argv, t_monitor *data)
{
	data->args.meal_limit = false;
	if (argc == 6)
		data->args.meal_limit = true;
	if (ft_atoul(argv[1], &data->nb_philos) != 0)
		return (-1);
	if (ft_atoul(argv[2], &data->args.time_die) != 0)
		return (-1);
	if (ft_atoul(argv[3], &data->args.time_eat) != 0)
		return (-1);
	if (ft_atoul(argv[4], &data->args.time_sleep) != 0)
		return (-1);
	if (data->args.meal_limit)
		if (ft_atoul(argv[5], &data->args.max_meal) != 0)
			return (-1);
	if (init_forks(data) != 0)
		return (-2);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (free_ret(data->forks, -2));
	if (init_philos(data) != 0)
		return (free_ret(data->forks, -2));
	data->loop = false;
	if (pthread_mutex_init(&data->loop_mutex, NULL) != 0)
		return (-2);
	return (0);
}

static int	init_forks(t_monitor *data)
{
	size_t	i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * data->nb_philos);
	if (!forks)
		return (-1);
	while (i < data->nb_philos)
	{
		forks[i].nb = i;
		forks[i].available = true;
		if (pthread_mutex_init(&(forks[i].mutex), NULL) != 0)
			return (-2);
		++i;
	}
	data->forks = forks;
	return (0);
}

static int	init_philos(t_monitor *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].nb = i;
		data->philos[i].nb_meal = 0;
		data->philos[i].args.time_die = data->args.time_die;
		data->philos[i].args.time_eat = data->args.time_eat;
		data->philos[i].args.time_sleep = data->args.time_sleep;
		data->philos[i].args.meal_limit = data->args.meal_limit;
		if (data->philos[i].args.meal_limit)
			data->philos[i].args.max_meal = data->args.max_meal;
		data->philos[i].l_fork = data->forks + i;
		data->philos[i].r_fork = data->forks + (i - 1);
		if (i == 0)
			data->philos[i].r_fork = data->forks + (data->nb_philos - 1);
		data->philos[i].loop = &data->loop;
		data->philos[i].loop_mutex = &data->loop_mutex;
		data->philos[i].start_time = &data->start_time;
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL) != 0)
			return (free_ret(data->philos, -1));
		++i;
	}
	return (0);
}
