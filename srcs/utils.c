/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:05:44 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/19 18:19:36 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdio.h>
#include "philo_data.h"
#include "utils.h"

static int	ft_isspace(int c)
{
	return ((c == ' ') || (c >= '\t' && c <= '\r'));
}

int	ft_atoul(const char *nptr, size_t *nb)
{
	size_t	i;
	uint8_t	any;

	i = 0;
	*nb = 0;
	any = 0;
	while (ft_isspace(nptr[i]))
		++i;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (ULLONG_MAX / 10 < *nb || *nb * 10 > ULLONG_MAX - (nptr[i] - 48))
			return (-1);
		*nb = *nb * 10 + (nptr[i++] - '0');
		if (!any)
			any = 1;
	}
	if (!any)
		return (-2);
	return (0);
}

int	free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

size_t	ft_gettimeofday(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

size_t	ts(size_t epoch)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (epoch - (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	secure_print(t_philo *philo, t_state mod)
{
	pthread_mutex_lock(philo->loop_mutex);
	if (*philo->loop == false)
		return (-1);
	pthread_mutex_unlock(philo->loop_mutex);
	if (mod == EAT)
		printf("%zu %zu is eating\n", ts(*philo->start_time), philo->nb);
	else if (mod == THINK)
		printf("%zu %zu is thinking\n", ts(*philo->start_time), philo->nb);
	else if (mod == SLEEP)
		printf("%zu %zu is sleeping\n", ts(*philo->start_time), philo->nb);
	else if (mod == FORK)
		printf("%zu %zu has taken a fork\n", ts(*philo->start_time), philo->nb);
	return (0);
}

void	pthread_mutex_unlock_lock(pthread_mutex_t *mtx)
{
	pthread_mutex_unlock(mtx);
	pthread_mutex_lock(mtx);
}
