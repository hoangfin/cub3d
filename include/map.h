/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:24:39 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/07 14:42:22 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	char	**content;
	int		width;
	int		height;
	int		row_count;
	int		col_count;
}	t_map;

t_map	*load_map(const char *map_file);
void	delete_map(t_map *map);

#endif