/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enclosed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:40:59 by emansoor          #+#    #+#             */
/*   Updated: 2024/10/01 18:30:58 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_map_row(char *to, char *from)
{
	uint32_t	index;

	index = 0;
	while (from[index])
	{
		to[index] = from[index];
		index++;
	}
	to[index] = '\0';
}

static char	**copy_matrix(t_map *map)
{
	char		**copy;
	uint32_t	rows;

	rows = 0;
	copy = (char **)ft_calloc(map->row_count + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	while (rows < map->row_count)
	{
		copy[rows] = (char *)ft_calloc(map->col_count + 1, sizeof(char));
		if (!copy[rows])
		{
			ft_del_str_arr(&copy);
			return (NULL);
		}
		copy_map_row(copy[rows], map->grid[rows]);
		rows++;
	}
	copy[rows] = NULL;
	return (copy);
}

static bool	floodfill(t_map *map, char **grid, int32_t row, int32_t col)
{
	if (
		row < 0 || (uint32_t)row >= map->row_count
		|| col < 0 || (uint32_t)col >= map->col_count
	)
		return (false);
	if (grid[row][col] == MAP_WALL || grid[row][col] == 'X')
		return (true);
	grid[row][col] = 'X';
	if (floodfill(map, grid, row - 1, col) == false)
		return (false);
	if (floodfill(map, grid, row + 1, col) == false)
		return (false);
	if (floodfill(map, grid, row, col - 1) == false)
		return (false);
	if (floodfill(map, grid, row, col + 1) == false)
		return (false);
	return (true);
}

bool	is_enclosed(t_map *map)
{
	char		**grid_copy;
	uint32_t	col;
	uint32_t	row;

	grid_copy = copy_matrix(map);
	if (!grid_copy)
		return (false);
	row = 0;
	while (row < map->row_count)
	{
		col = 0;
		while (col < map->col_count)
		{
			if (grid_copy[row][col] == MAP_PATH
				&& floodfill(map, grid_copy, row, col) == false)
			{				
				ft_del_str_arr(&grid_copy);
				return (false);
			}
			col++;
		}
		row++;
	}
	ft_del_str_arr(&grid_copy);
	return (true);
}
