/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:31:03 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/19 14:31:53 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>

int		free_ret(void *ptr, int ret);
size_t	ts(size_t epoch);
int		ft_atoul(const char *nptr, size_t *nb);
size_t	ft_gettimeofday(void);

#endif
