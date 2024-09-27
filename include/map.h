/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:06:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 23:14:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "MLX42.h"

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

t_map	*load_map(char *pathname);

int		check_file_end(int fd);
int		check_file_permissions(char *file);
int		get_map(t_map *map, char *data, int fd, char *pathname);
int		get_texture(t_map *specs, char *data, int *error);
int		map_edge(char *line);
int		print_content_error(void *str, int *error);
int		validate_map(t_map *map);
int		validate(char *map_file);
int		verify_fileformat(char *filename, char *filetype);

void	copy_line(t_map *map, char *line, unsigned int index);
void	delete_map(t_map *map);
void	get_color(t_map *specs, char *data, int *error, int *color_status);

bool	door_check(t_map *map);
bool	ft_has_spaces_only_cubed(char *str);
bool	is_enclosed(t_map *map);
bool	is_wall(int32_t x, int32_t y, t_map *map);
bool	too_many_commas(char *str);

#endif
