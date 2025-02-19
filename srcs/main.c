/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:00:47 by kporceil          #+#    #+#             */
/*   Updated: 2025/02/19 19:24:46 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_data.h"
#include "parsing.h"

void	print_args(t_monitor *data)
{
	for(size_t i = 0; i < data->nb_philos; ++i)
	{
		printf("philo numero : %zu\n", data->philos[i].nb);
		printf("\ttime to die : %zu\n\ttime to eat : %zu\n\ttime to sleep : %zu\n", data->philos[i].args.time_die, data->philos[i].args.time_eat, data->philos[i].args.time_sleep);
		printf("\tmeal limit : %s\n", data->philos[i].args.meal_limit ? "true" : "false");
		if (data->philos[i].args.meal_limit)
			printf("\t\tmax meal : %zu\n", data->philos[i].args.max_meal);
		printf("\tr_fork nb : %zu\n", data->philos[i].r_fork->nb);
		printf("\tl_fork nb : %zu\n", data->philos[i].l_fork->nb);
		if (&data->loop == data->philos[i].loop)
			printf("\tloop bool successfull sync\n");
	 	else
	 		printf("\tERROR: loop bool\n");
		if (&data->loop_mutex == data->philos[i].loop_mutex)
			printf("\tmutex_loop successfully sync\n");
	 	else
	 		printf("\tERROR: loop_mutex");
	}
	
}

int	main(int argc, char **argv)
{
	t_monitor	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrongs args");
		return (1);
	}
	if (init_args(argc, argv, &data) != 0)
		return (2);
	print_args(&data);
}
