/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_diagonal_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:44:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/09 08:45:09 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_diagonal_move(
	int32_t start_x,
	int32_t start_y,
	int32_t end_x,
	int32_t end_y
)
{
	const int32_t	start_row = start_y / MAP_CELL_SIZE;
	const int32_t	start_col = start_x / MAP_CELL_SIZE;
	const int32_t	end_row = end_y / MAP_CELL_SIZE;
	const int32_t	end_col = end_x / MAP_CELL_SIZE;

	if (end_row == start_row - 1 && end_col == start_col -1)
		return (true);
	if (end_row == start_row - 1 && end_col == start_col + 1)
		return (true);
	if (end_row == start_row + 1 && end_col == start_col + 1)
		return (true);
	if (end_row == start_row + 1 && end_col == start_col - 1)
		return (true);
	return (false);
}
