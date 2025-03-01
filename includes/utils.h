/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:31:03 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/26 20:20:54 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include "philo_data.h"

int		free_ret(void *ptr, int ret);
int		free_fork(t_philo *philo, int ret);
void	update_last_meal(t_philo *philo, size_t time);
bool	take_fork(t_fork *fork);
bool	check_meal_limit(t_philo *philo);
void	wait_start(t_philo *philo);
size_t	ts(size_t epoch);
int		ft_atoul(const char *nptr, size_t *nb);
size_t	ft_gettimeofday(void);
int		secure_print(t_philo *philo, t_state mod, size_t time);
void	pthread_mutex_unlock_lock(pthread_mutex_t *mtx);
void	ft_usleep(size_t usec);

#endif
