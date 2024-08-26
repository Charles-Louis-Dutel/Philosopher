/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:17:00 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/21 09:26:42 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
	{
		write(2, ERR_MSG_WRITE, ft_strlen(ERR_MSG_WRITE));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
