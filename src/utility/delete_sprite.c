/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:39:24 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 14:55:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

void	delete_sprite(t_sprite *sprite, mlx_t *mlx)
{
	uint32_t	row;
	uint32_t	col;

	if (sprite == NULL || sprite->frames == NULL)
		return ;
	row = 0;
	while (row < sprite->row_count)
	{
		col = 0;
		while (sprite->frames[row] != NULL && col < sprite->col_count)
		{
			mlx_delete_image(mlx, sprite->frames[row][col]);
			col++;
		}
		free(sprite->frames[row]);
		row++;
	}
	free(sprite->frames);
	free(sprite);
}
