/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:48:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/18 17:00:48 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_datastruct	*data;

	if (argc < 5 || argc > 6)
		return (err_msg(ERR_MSG_ARGS), EXIT_FAILURE);
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_datastruct));
	if (!data)
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	if (init_datastruct(data, argv) == EXIT_FAILURE)
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	if (data->min_meal == 0)
		return (EXIT_SUCCESS);
	init_philosophers(data);
	free(data->ph);
	free(data);
	return (EXIT_SUCCESS);
}
