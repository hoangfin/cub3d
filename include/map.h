/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:06:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/28 21:33:07 by hoatran          ###   ########.fr       */
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
int		get_color(t_map *specs, char *data, int *error, int *color_status);
int		get_map(t_map *map, char *data, int fd, char *pathname);
int		get_texture(t_map *specs, char *data, int *error);
int		map_edge(char *line);
int		print_content_error(void *str, int *error);
int		validate_color(char *cleaned_color);
int		validate_map(t_map *map);
int		validate(char *map_file);
int		verify_fileformat(char *filename, char *filetype);

bool	door_check(t_map *map);
bool	has_spaces_only(char *str);
bool	is_clean_color(char *data, int chr);
bool	is_clean_texture(char *data, char *str);
bool	is_enclosed(t_map *map);
bool	is_valid_row(char *line);
bool	too_many_commas(char *str);

void	copy_line(t_map *map, char *line, unsigned int index);
void	delete_map(t_map *map);

#endif
