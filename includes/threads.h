/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:03:41 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/23 01:13:09 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "philo_data.h"

int		starting_threads(t_monitor *data);
void	update_last_meal(t_philo *philo, size_t time);
int		monitor_threads(t_monitor *data);
int		end_thread(t_monitor *data);
int		check_die(t_philo *philo, t_monitor *data);
int		end_loop(t_monitor *data);
void	*philo_routine(void *args);
int		philo_eat(t_philo *philo);

#endif
