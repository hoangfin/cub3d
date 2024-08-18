/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 11:12:12 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int32_t	color_check(char **colors, int index)
{
	t_bool	overflow;
	int32_t	color;
	
	if (!colors[index] || ft_strcmp(colors[index], "\0") == 0)
		return (-1);
	overflow = false;
	color = (int32_t)ft_atoi(colors[index], &overflow);
	if (overflow || color < 0 || color > 255)
	{
		return (-1);
	}
	return (color);
}

static int	verify_colors(t_map *specs, char **colors, int id)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;
	
	red = color_check(colors, 0);
	green = color_check(colors, 1);
	blue = color_check(colors, 2);
	ft_matrix_delete(&colors);
	if (red < 0 || green < 0 || blue < 0)
	{
		return (print_content_error(NULL, 2.4));
	}
	if (id == 1)
		specs->color_floor = color(red, green, blue, 1.0);
	else if (id == 2)
		specs->color_ceiling = color(red, green, blue, 1.0);
	return (0);
}

static int	extract_color(t_map *specs, char *line, int identifier)
{
	char	*extract;
	char	**color;
	char	set[2];

	set[0] = '\n';
	set[1] = ' ';
	extract = ft_strtrim(line + 1, set);
	if (!extract || extract[0] == '\0')
		return (print_content_error(extract, 2.1));
	color = ft_split(extract, ',');
	if (!color)
		return (print_content_error(extract, 2.2)); // what if malloc fails in split??
	free(extract);
	if (ft_matrix_count_rows(color) != 3)
	{
		ft_matrix_delete(&color);
		return (print_content_error(NULL, 2.3));
	}
	return (verify_colors(specs, color, identifier));
}

int	get_color(t_map *specs, char *data)
{
	char	*content;
	
	content = data;
	if (ft_strnstr(content, "F", 1))
		return (extract_color(specs, content, 1));
	content = data;
	if (ft_strnstr(content, "C", 1))
		return (extract_color(specs, content, 2));
	return (0);
}
