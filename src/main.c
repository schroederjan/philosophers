/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschroed <jschroed@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:50 by jschroed          #+#    #+#             */
/*   Updated: 2024/10/20 18:00:26 by jschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (ERROR);
	if (initialize_simulation(&data) != 0)
		return (ERROR);
	start_simulation(&data);
	print_statistics(&data);
	cleanup_simulation(&data);
	return (SUCCESS);
}
