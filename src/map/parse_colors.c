/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/26 13:40:27 by emansoor         ###   ########.fr       */
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

static int	verify_colors(t_map *map, char **colors, int id, int *error)
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
		return (print_content_error(NULL, error));
	}
	if (id == 1)
		map->color_floor = color(red, green, blue, 1.0);
	else if (id == 2)
		map->color_ceiling = color(red, green, blue, 1.0);
	return (0);
}

static int	extract_color(t_map *map, char *line, int identifier, int *error)
{
	char	*extract;
	char	**color;
	char	set[2];

	set[0] = '\n';
	set[1] = ' ';
	color = NULL;
	extract = ft_strtrim(line + 1, set);
	if (!extract)
	{
		*error = 1;
		write(STDERR_FILENO, "Error\nft_strtrim\n", 17);
		return (1);
	}
	color = ft_split(extract, ',');
	if (extract[0] == '\0' || !color)
		return (print_content_error(extract, error));
	free(extract);
	if (ft_matrix_count_rows(color) != 3)
	{
		ft_matrix_delete(&color);
		return (print_content_error(NULL, error));
	}
	return (verify_colors(map, color, identifier, error));
}

int	get_color(t_map *map, char *data, int *error)
{
	char	*content;

	content = data;
	content = ft_strnstr(content, "F", 1);
	if (content)
		return (extract_color(map, content, 1, error));
	content = data;
	content = ft_strnstr(content, "C", 1);
	if (content)
		return (extract_color(map, content, 2, error));
	return (0);
}
