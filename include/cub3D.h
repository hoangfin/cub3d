/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:22:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/28 21:11:59 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 1280
# define HEIGHT 960
# define FOV (M_PI / 3)

# define MAP_SPACE ' '
# define MAP_PATH '0'
# define MAP_WALL '1'
# define MAP_PLAYER "NSEW"
# define MAP_DOOR 'D'
# define MAP_CELL_SIZE 20
# define MAP_PLAYER_SIZE 16

# define MINIMAP_X 30
# define MINIMAP_Y 30
# define MINIMAP_SIZE 200

# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "MLX42.h"
# include "libft.h"
# include "map.h"
# include "utility.h"
# include "player.h"
# include "ray.h"
# include "door.h"

typedef struct s_asset
{
	mlx_image_t	*walls[4];
	mlx_image_t	*obstacle;
	mlx_image_t	*door;
	mlx_image_t	*navigator;
	t_sprite	*sprite_door;
	t_sprite	*sprite_wand;
}	t_asset;

typedef struct s_image
{
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*scene;
	mlx_image_t	*minimap;
	mlx_image_t	*minimap_bg;
	mlx_image_t	*map;
}	t_image;

typedef struct s_cub3D
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	player;
	t_door		*doors;
	t_ray		*rays;
	int32_t		mouse_x;
	int32_t		mouse_y;
	t_asset		asset;
	t_image		image;
}	t_cub3D;

void	destroy(t_cub3D *cub3D);
void	init_assets(t_cub3D *cub3d);
void	init_doors(t_cub3D *cub3d);
void	init_hooks(t_cub3D *cub3d);
void	init_images(t_cub3D *cub3d);
void	init_player(t_cub3D *cub3d);
void	init(t_cub3D *cub3D, char *pathname);
void	render_images(t_cub3D *cub3d);

void	dda(t_ray *ray, t_cub3D *cub3d);
void	find_hit_point(
			t_ray *ray,
			t_cub3D *cub3d,
			bool (*is_hit)(int32_t , int32_t , void *)
		);
void	set_distance(t_ray *ray, t_cub3D *cub3d);
void	set_end_point(int32_t row_hit, int32_t col_hit, t_ray *ray);
void	set_hit_texture(int32_t row, int32_t col, t_ray *ray, t_cub3D *cub3d);

void	draw_map(mlx_image_t *map, t_cub3D *cub3D);
void	draw_minimap(mlx_image_t *minimap, t_cub3D *cub3D);
void	draw_player(t_cub3D *cub3d);
void	draw_scene(t_cub3D *cub3d);

void 	close_handler(void	*param);
void	handle_collisions(t_cub3D *cub3d);
void 	loop_handler(void *param);
void	process_inputs(t_cub3D *cub3D);
void	update(t_cub3D *cub3d, double elapsed_time);
void	update_ui(t_cub3D *cub3d);

t_door	*get_door(int32_t row, int32_t col, t_cub3D *cub3d);
bool	is_valid_position(int32_t x, int32_t y, t_cub3D *cub3d);

#endif
