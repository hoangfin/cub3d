/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/18 23:18:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D	cub3d;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\nInvalid arguments\n", 24);
		return (EXIT_FAILURE);
	}
	ft_bzero(&cub3d, sizeof(t_cub3D));
	init(&cub3d, argv[1]);
	mlx_loop(cub3d.mlx);
	destroy(&cub3d);
	return (EXIT_SUCCESS);
}
