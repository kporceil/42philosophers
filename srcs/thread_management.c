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
#include <pthread.h>

int	create_philo(t_philo_data *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->philo_nb)
	{
		if (pthread_create(philo[i]->thread, NULL, routine, philo) != 0)
			return (-1);

	}
}
