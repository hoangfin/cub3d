/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:39:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/19 14:11:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_door(t_door *door, int32_t row, int32_t col, t_cub3D *cub3d)
{
	door->x = col * MAP_CELL_SIZE;
	door->y = row * MAP_CELL_SIZE;
	door->state = DOOR_CLOSED;
	door->image = mlx_new_image(cub3d->mlx, 373, 476);
	if (door->image == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
	copy_pixels(door->image, cub3d->asset.door, 373, 476);
}

void	init_doors(t_cub3D *cub3d)
{
	uint32_t	row;
	uint32_t	col;
	int32_t		i;

	cub3d->doors = (t_door *)ft_calloc(cub3d->map->door_count, sizeof(t_door));
	if (cub3d->doors == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		destroy(cub3d);
		exit(1);
	}
	row = 0;
	i = 0;
	while (row < cub3d->map->row_count)
	{
		col = 0;
		while (col < cub3d->map->col_count)
		{
			if (cub3d->map->grid[row][col] == MAP_DOOR)
				init_door(&cub3d->doors[i++], row, col, cub3d);
			col++;
		}
		row++;
	}
}
