/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:46:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 14:03:08 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	missing_map(t_map *specs)
{
	if (specs->wall_paths[0] && specs->wall_paths[1] && specs->wall_paths[2]
		&& specs->wall_paths[3] && specs->color_ceiling && specs->color_floor
		&& !specs->grid)
		return (1);
	return (0);
}

int	extract_data(t_map *specs, char *data)
{
	//printf("current line: |%s|\n", data);
	if (get_texture(specs, data) > 0 || get_color(specs, data) > 0)
		return (1);
	return (0);
}
