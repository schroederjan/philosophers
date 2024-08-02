/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:25:07 by jschroed          #+#    #+#             */
/*   Updated: 2024/05/30 09:52:06 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(const char *msg, int error_code, t_data data)
{
	const char	*error_prefix;

	error_prefix = "Error: ";
	write(STDERR_FILENO, error_prefix, ft_strlen(error_prefix));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (data == NULL)
		free(data)

	exit (error_code);
}
