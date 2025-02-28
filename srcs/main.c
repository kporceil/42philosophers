/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:00:47 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/23 01:30:30 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "threads.h"
#include "philo_data.h"
#include "parsing.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_monitor	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrongs args.\n");
		return (1);
	}
	if (init_args(argc, argv, &data) != 0)
	{
		printf("Wrongs args.\n");
		return (2);
	}
	if (starting_threads(&data) != 0)
		return (free_ret(data.forks, free_ret(data.philos, 3)));
	if (monitor_threads(&data) != 0)
		return (free_ret(data.forks, free_ret(data.philos, 4)));
	if (end_thread(&data) != 0)
		return (free_ret(data.forks, free_ret(data.philos, 5)));
	return (free_ret(data.forks, free_ret(data.philos, 0)));
}
