/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 11:57:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	save_color(t_map *specs, int color, int id, int index)
{
	if (id == 1 && specs->floor_colors[index] != -1 || id == 2 && specs->ceiling_colors[index])
		return (1);
}

static int	verify_colors(t_map *specs, char **colors, int id)
{
	t_bool	overflow;
	int		color;
	int		index;
	
	index = 0;
	overflow = false;
	while (index < 3)
	{
		color = ft_atoi(colors[index], &overflow);
		if (overflow || color < 0 || color > 255
			|| save_color(specs, color, id, index) > 0)
		{
			ft_matrix_delete(&colors);
			return (print_content_error(NULL));
		}
		index++;
	}
	return (0);
}

/* static int	copy_colors(t_map *specs, char **color, int id)
{
	if (verify_colors(color) > 0)
		return (1);
	if (id == 1 && specs->f)
		return (print_content_error(colors));
	else if (id == 1 && !specs->f)
		specs->f = colors;
	else if (id == 2 && specs->c)
		return (print_content_error(colors));
	else if (id == 2 && !specs->c)
		specs->c = colors;
	return (0);
} */

static int	extract_color(t_map *specs, char *line, int identifier)
{
	char	*extract;
	char	**color;

	extract = ft_strtrim(line + 1, " ");
	if (!extract || extract[0] == '\0')
		return (print_content_error(extract));
	color = ft_split(extract, ',');
	if (!color)
		return (print_content_error(extract)); // what if malloc fails in split??
	free(extract);
	if (ft_matrix_count_rows(color) != 3)
	{
		ft_matrix_delete(&color);
		return (print_content_error(NULL));
	}
	//return (copy_colors(specs, color, identifier));
}

int	get_color(t_map *specs, char *data)
{
	char	*content;
	
	if (specs->north_wall && specs->south_wall
		&& specs->west_wall && specs->east_wall)
	{
		content = data;
		if (ft_strnstr(content, "F", 1))
			return (extract_color(specs, content, 1));
		content = data;
		if (ft_strnstr(content, "C", 1))
			return (extract_color(specs, content, 2));
	}
	return (print_content_error(NULL));
}
