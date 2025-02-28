/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:05:44 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/26 20:20:48 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
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
	return (ft_gettimeofday() - epoch);
}
