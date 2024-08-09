/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:50:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/08 23:08:41 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_character(mlx_t *mlx, t_character *character)
{
	if (character == NULL)
		return ;
	mlx_delete_image(mlx, character->image);
	free(character);
}
