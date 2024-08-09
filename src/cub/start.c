/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:08:01 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/08 23:07:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	draw_images(t_game *game, int32_t row, int32_t col)
{
	const int32_t	x = game->map_x + col * RENDER_PIXELS;
	const int32_t	y = game->map_y + row * RENDER_PIXELS;

	if (game->map[row][col] == '1')
		mlx_image_to_window(game->mlx, game->wall, x, y);
	if (game->map[row][col] == 'C')
		mlx_image_to_window(game->mlx, game->collectible, x, y);
	if (game->map[row][col] == 'E')
		mlx_image_to_window(game->mlx, game->exit, x, y);
	if (mlx_errno)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), -1);
	return (0);
}

static int	draw_floor(t_game *game)
{
	int32_t	row;
	int32_t	col;
	int32_t	x;
	int32_t	y;

	row = 0;
	while (row < game->row_count)
	{
		col = 0;
		while (col < game->col_count)
		{
			x = game->map_x + col * RENDER_PIXELS;
			y = game->map_y + row * RENDER_PIXELS;
			if (mlx_image_to_window(game->mlx, game->space, x, y) == -1)
				return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), -1);
			col++;
		}
		row++;
	}
	return (0);
}

static int	draw_enemies(mlx_t *mlx, t_character **enemies)
{
	while (*enemies != NULL)
	{
		if (mlx_image_to_window(\
			mlx, \
			(*enemies)->image, \
			(*enemies)->x, \
			(*enemies)->y \
		) == -1)
			return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), -1);
		enemies++;
	}
	return (0);
}

static int	draw(t_game *game)
{
	int32_t	row;
	int32_t	col;

	if (draw_floor(game) < 0)
		return (-1);
	row = 0;
	while (row < game->row_count)
	{
		col = 0;
		while (col < game->col_count)
		{
			if (draw_images(game, row, col) < 0)
				return (-1);
			col++;
		}
		row++;
	}
	if (mlx_image_to_window(
			game->mlx, game->player->image, game->player->x, game->player->y \
	) == -1)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), -1);
	if (draw_enemies(game->mlx, game->enemies) < 0)
		return (-1);
	return (0);
}

int		start_cub(t_cub3D *cub)
{
	// draw_floor();
	// draw_ceiling();
	draw_minimap(cub);
	mlx_image_t	*image;
	image->
}
