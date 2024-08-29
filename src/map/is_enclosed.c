/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enclosed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:40:59 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/23 11:41:39 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	check_first_row(t_map *map, char *row, uint32_t row_id)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (row[col] == MAP_SPACE)
		{
			row_id = 1;
			while (row_id < map->row_count)
			{
				if (map->grid[row_id][col] == MAP_SPACE)
					row_id++;
				else if (map->grid[row_id][col] == MAP_WALL)
					break ;
				else
					return (false);
			}
			if (row_id == map->row_count)
				return (false);
		}
		else if (row[col] != MAP_WALL)
			return (false);
		col++;
	}
	return (true);
}

static t_bool	check_last_row(t_map *map, char *row, uint32_t row_id)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (row[col] == MAP_SPACE)
		{
			row_id = map->row_count - 2;
			while (row_id > 0)
			{
				if (map->grid[row_id][col] == MAP_SPACE)
					row_id--;
				else if (map->grid[row_id][col] == MAP_WALL)
					break ;
				else
					return (false);
			}
			if (row_id < 1)
				return (false);
		}
		else if (row[col] != MAP_WALL)
			return (false);
		col++;
	}
	return (true);
}

static t_bool	check_ends(t_map *map, char *row, uint32_t row_id)
{
	if (row_id == 0)
		return (check_first_row(map, row, row_id));
	if (row_id == map->row_count - 1)
		return (check_last_row(map, row, row_id));
	return (false);
}

static t_bool	check_edges(t_map *map, char *row)
{
	int	col;

	col = 0;
	if (col == 0 && row[col] == MAP_SPACE)
	{
		while (row[col] == MAP_SPACE)
			col++;
	}
	if (row[col] != MAP_WALL)
		return (false);
	col = map->col_count - 1;
	if (row[col] == MAP_SPACE)
	{
		while (row[col] == MAP_SPACE)
			col--;
	}
	if (row[col] != MAP_WALL)
		return (false);
	return (true);
}

t_bool	is_enclosed(t_map *map)
{
	uint32_t	row;

	row = 0;
	while (map->grid[row])
	{
		if (row == 0 || row == map->row_count - 1)
		{
			if (check_ends(map, map->grid[row], row) == false)
				return (false);
		}
		if (row > 0 && row < map->row_count - 1)
		{
			if (check_edges(map, map->grid[row]) == false)
				return (false);
		}
		row++;
	}
	return (true);
}
