/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:22:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/23 23:38:02 by hoatran          ###   ########.fr       */
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
# define MAP_FOE 'F'
# define MAP_CELL_SIZE 20
# define MAP_PLAYER_SIZE 14

# define MINIMAP_X 30
# define MINIMAP_Y 30
# define MINIMAP_SIZE 200

# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "player.h"
# include "sprite.h"
# include "ray.h"
# include "door.h"
# include "MLX42.h"

typedef struct s_asset
{
	mlx_image_t	*walls[4];
	mlx_image_t	*obstacle;
	mlx_image_t	*navigator;
	t_sprite	*sprite_door;
	t_sprite	*sprite_wand;
}	t_asset;

typedef struct s_image
{
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	mlx_image_t	*scene;
	mlx_image_t	*minimap;
	mlx_image_t	*minimap_bg;
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
	uint32_t	door_count;
}	t_map;

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


void		create_images(t_cub3D *cub3d);
void		destroy(t_cub3D *cub3D);
void		init_doors(t_cub3D *cub3d);
void		init_player(t_cub3D *cub3d);
void		init(t_cub3D *cub3D, char *pathname);

void		dda(t_ray *ray, t_cub3D *cub3d);
void		find_hit_point(int32_t *row, int32_t *col, t_ray *ray, t_cub3D *cub3d);
void		set_distance(t_ray *ray, t_cub3D *cub3d);
void		set_end_point(int32_t row_hit, int32_t col_hit, t_ray *ray);
void		set_hit_texture(int32_t row, int32_t col, t_ray *ray, t_cub3D *cub3d);

void		update_doors(t_cub3D *cub3d, double elapsed_time);
void		update_rays(t_cub3D *cub3d);

void		draw_map(mlx_image_t *map, t_cub3D *cub3D);
void		draw_minimap(mlx_image_t *minimap, t_cub3D *cub3D);
void		draw_player(t_cub3D *cub3d);
void		draw_scene(t_cub3D *cub3d);
void		draw_texture(t_cub3D *cub3D, int x, int start_y, int lineheight);

void 		close_handler(void	*param);
void		handle_collisions(t_cub3D *cub3d);
void 		loop_handler(void *param);
void		process_inputs(t_cub3D *cub3D);
void		update(t_cub3D *cub3d, double elapsed_time);
void		update_ui(t_cub3D *cub3d);

void		clear_image(mlx_image_t *image);
uint32_t	color(int32_t r, int32_t g, int32_t b, int32_t a);
void		fill(mlx_image_t *image, uint32_t color);
t_door		*get_door(int32_t row, int32_t col, t_cub3D *cub3d);
uint8_t		*get_pixels(mlx_image_t *image, int32_t x, int32_t y);
bool		is_equal(double a, double b);
bool		is_valid_position(int32_t x, int32_t y, t_cub3D *cub3d);
bool		is_wall(int32_t x, int32_t y, t_cub3D *cub3d);
mlx_image_t	*load_png(mlx_t *mlx, const char *pathname);
int32_t		max(int32_t a, int32_t b);
void		copy_pixels(
				mlx_image_t *dest,
				mlx_image_t *src,
				int32_t offset_x,
				int32_t offset_y
			);

/*							PARSING							*/
t_map	*load_map(char *pathname);
int		check_file_permissions(char *file);
int		verify_fileformat(char *filename, char *filetype);
int		validate(char *map_file);
void	get_color(t_map *specs, char *data, int *error, int *color_status);
int		get_texture(t_map *specs, char *data, int *error);
int		get_map(t_map *map, char *data, int fd, char *pathname);
t_bool	ft_has_spaces_only_cubed(char *str);
int		print_content_error(void *str, int *error);
int		map_edge(char *line);
int		check_file_end(int fd);
void	copy_line(t_map *map, char *line, unsigned int index);
int		validate_map(t_map *map);
t_bool	is_enclosed(t_map *map);
t_bool	too_many_commas(char *str);
void	delete_map(t_map *map);

#endif
