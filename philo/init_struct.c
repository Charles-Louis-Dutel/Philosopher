/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:54:09 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 16:58:40 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_args *args, char **argv)
{
	args->philo_num = ft_atoi(argv[1]);
	args->death_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->must_eat = -1;
	if (argv[5])
		args->must_eat = ft_atoi(argv[5]);
	args->start_time = 0;
	args->dead_flag = 0;
	return (EXIT_SUCCESS);
}
