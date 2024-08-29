/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/09 15:11:02 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D	cub3D;
	
	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\nInvalid number of arguments\n", 34);
		return (EXIT_FAILURE);
	}	
	if (init(&cub3D, argv[1]) != 0 || start(&cub3D) != 0)
		return (EXIT_FAILURE);
	destroy(&cub3D);
	return (EXIT_SUCCESS);
}
