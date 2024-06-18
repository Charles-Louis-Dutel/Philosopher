/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:43:41 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 18:50:34 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_msg(char *error_msg)
{
	if (write(2, error_msg, ft_strlen(error_msg)) == -1)
		write(2, ERR_MSG_WRITE, ft_strlen(ERR_MSG_WRITE));
}
