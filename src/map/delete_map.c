/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:21 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/21 14:09:05 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_map(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < 4)
		free(map->wall_paths[i++]);
	if (map->grid != NULL)
		ft_del_str_arr(&map->grid);
	free(map);
}
