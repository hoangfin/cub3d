/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:29:43 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 20:38:02 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color)
{
    // Bresenham's line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        // Set pixel at (x0, y0)
        mlx_put_pixel(img, x0, y0, color);

        // Break if the end point is reached
        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;

        // Adjust error and coordinates accordingly
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void	draw_scene(t_cub3D *cub3d)
{
	const double	camera_plane_distance = (WIDTH / 2) / tan(M_PI / 6);
	int32_t			i;
	double			wall_height;

	i = 0;
	clear_image(cub3d->image.scene);
	while (i < WIDTH)
	{
		wall_height = (10 / cub3d->rays[i].distance) * camera_plane_distance;
		if (wall_height > HEIGHT)
			wall_height = HEIGHT;
		draw_line(
			cub3d->image.scene,
			i,
			HEIGHT / 2 - wall_height / 2,
			i,
			HEIGHT / 2 + wall_height / 2,
			color(238, 200 , 125, 255)
		);
		i++;
	}
}
