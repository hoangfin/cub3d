/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:22:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/28 10:29:53 by emansoor         ###   ########.fr       */
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

t_character	*new_character(mlx_t *mlx, int32_t x, int32_t y, int32_t angle);

//int		init(t_cub3D *cub3D, const char *pathname);
int		init(t_cub3D *cub3D, char *pathname);
int		start(t_cub3D *cub3D);
void	destroy(t_cub3D *cub3D);

uint32_t	color(int32_t r, int32_t g, int32_t b, int32_t a);
void		fill(mlx_image_t *image, uint32_t color);
mlx_image_t	*load_png(mlx_t *mlx, const char *pathname);
void		copy_pixels(mlx_image_t *dest,mlx_image_t *src,int32_t offset);

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