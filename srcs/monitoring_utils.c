/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:00:16 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/28 14:00:31 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void	ft_usleep(size_t usec)
{
	size_t	start;

	start = ft_gettimeofday();
	while (ft_gettimeofday() - start < usec / 1000)
		usleep(100);
}
