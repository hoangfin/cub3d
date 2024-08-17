/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:22:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/17 15:56:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 960

# define MAP_SPACE ' '
# define MAP_PATH '0'
# define MAP_WALL '1'
# define MAP_DOOR 'D'
# define MAP_FOE 'F'
# define MAP_CELL_SIZE 16

# define MINIMAP_SIZE 256

# include "libft.h"
# include "MLX42.h"

typedef struct s_image
{
	mlx_image_t	*walls[4];
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	mlx_image_t	*obstacle;
	mlx_image_t	*dot;
	mlx_image_t	*path;
	mlx_image_t	*minimap;
	mlx_image_t	*map;
}	t_image;

typedef struct s_map
{
	char		**grid;
	char		*wall_paths[4];
	uint32_t	width;
	uint32_t	height;
	uint32_t	row_count;
	uint32_t	col_count;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
}	t_map;

typedef struct s_ray
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	double	length;
	double	angle;
}	t_ray;

typedef enum e_character_state
{
	PLAYER_IDLE,
	PLAYER_MOVING,
	PLAYER_DIED,
	ENEMY_IDLE,
	ENEMY_MOVING,
	ENEMY_ATTACKING,
	ENEMY_DIED,
}	t_character_state;

typedef struct s_character
{
	mlx_image_t			*image;
	int					x;
	int					y;
	int					angle;
	t_character_state	state;
}	t_character;

typedef struct s_cub3D
{
	mlx_t		*mlx;
	t_map		*map;
	t_character	*player;
	t_ray		*rays;
	int			ray_count;
	int			fov;
}	t_cub3D;

t_map	*load_map(const char *map_file);
void	delete_map(t_map *map);

t_character	*new_character(mlx_t *mlx, int32_t x, int32_t y, int32_t angle);

int		init(t_cub3D *cub3D, const char *pathname);
int		start(t_cub3D *cub3D);
void	destroy(t_cub3D *cub3D);

uint32_t	color(int32_t r, int32_t g, int32_t b, int32_t a);
void		fill(mlx_image_t *image, uint32_t color);
mlx_image_t	*load_png(mlx_t *mlx, const char *pathname);
void		copy_pixels(mlx_image_t *dest,mlx_image_t *src,int32_t offset);

#endif