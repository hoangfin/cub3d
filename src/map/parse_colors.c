/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/12 13:36:51 by emansoor         ###   ########.fr       */
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

static void	verify_colors(t_map *map, char **colors, int id, int *error)
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
		print_content_error(NULL, error);
		return ;
	}
	if (id == 1)
		map->color_floor = color(red, green, blue, 255);
	else if (id == 2)
		map->color_ceiling = color(red, green, blue, 255);
}

static char	*extract_color(char *line, int *error)
{
	char	*extract;
	char	set[2];

	set[0] = '\n';
	set[1] = ' ';
	extract = NULL;
	extract = ft_strtrim(line + 1, set);
	if (!extract)
	{
		*error = 1;
		write(STDERR_FILENO, "Error\nft_strtrim\n", 17);
		return (NULL);
	}
	if (extract[0] == '\0' || too_many_commas(extract))
	{
		print_content_error(extract, error);
		return (NULL);
	}
	return (extract);
}

static void	save_color(t_map *map, char *line, int identifier, int *error)
{
	char	*color;
	char	**colors;

	colors = NULL;
	color = extract_color(line, error);
	if (!color)
		return ;
	colors = ft_split(color, ',');
	if (!colors)
	{
		print_content_error(color, error);
		return ;
	}
	free(color);
	if (ft_matrix_count_rows(colors) != 3)
	{
		ft_matrix_delete(&colors);
		print_content_error(NULL, error);
		return ;
	}
	verify_colors(map, colors, identifier, error);
}

void	get_color(t_map *map, char *data, int *error, int *color_status)
{
	char	*content;

	content = data;
	content = ft_strnstr(content, "F", 1);
	if (content)
	{
		(*color_status)++;
		save_color(map, content, 1, error);
		return ;
	}
	content = data;
	content = ft_strnstr(content, "C", 1);
	if (content)
	{
		(*color_status)++;
		save_color(map, content, 2, error);
	}
}
