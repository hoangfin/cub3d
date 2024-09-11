/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/07 17:01:07 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D	*cub3d;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\nInvalid arguments\n", 24);
		return (EXIT_FAILURE);
	}
	cub3d = (t_cub3D *)malloc(sizeof(t_cub3D));
	if (!cub3d)
	{
		write(STDERR_FILENO, "Error\nmalloc\n", 13);
		return (EXIT_FAILURE);
	}
	if (init(cub3d, argv[1]) != 0)
		return (EXIT_FAILURE);
	mlx_loop(cub3d->mlx);
	destroy(cub3d);
	return (EXIT_SUCCESS);
}
