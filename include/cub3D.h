/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:22:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 14:19:46 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RENDER_PIXELS 32

# define DOOR_CHAR 'D'
# define ENEMY_CHAR 'F'

# include "libft.h"
# include "MLX42.h"

typedef struct s_map
{
	char		**grid;
	uint32_t	width;
	uint32_t	height;
	uint32_t	row_count;
	uint32_t	col_count;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
	mlx_image_t	*walls[4];
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	mlx_image_t	*minimap;
	mlx_image_t	*map;
	mlx_image_t	*map_wall;
	mlx_image_t	*map_player;
	mlx_image_t	*map_path;
	mlx_image_t	*map_space;
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