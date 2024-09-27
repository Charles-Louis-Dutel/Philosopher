/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:48:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/27 19:30:38 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_datastruct	*data;
	int				res;

	if (argc < 5 || argc > 6)
		return (err_msg(ERR_MSG_ARGS), EXIT_FAILURE);
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_datastruct));
	if (!data)
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	res = init_datastruct(data, argv);
	if (res == EXIT_FAILURE)
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	if (res == 2)
		return (free(data), EXIT_SUCCESS);
	init_philosophers(data);
	free(data->ph);
	free(data);
	return (EXIT_SUCCESS);
}
