/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/27 16:28:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int32_t	check_color(char *color_data)
{
	char	*cleaned_color;
	int32_t	color;

	color = -1;
	cleaned_color = ft_strtrim(color_data, " ");
	if (!cleaned_color || ft_strcmp(cleaned_color, "\0") == 0)
	{
		if (cleaned_color)
			free(cleaned_color);
		return (color);
	}
	color = validate_color(cleaned_color);
	return (color);
}

static void	save_rgb_model(t_map *map, char **colors, int id, int *error)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;

	red = check_color(colors[0]);
	green = check_color(colors[1]);
	blue = check_color(colors[2]);
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
	save_rgb_model(map, colors, identifier, error);
}

int	get_color(t_map *map, char *data, int *error, int *color_status)
{
	char	*content;

	content = data;
	content = ft_strnstr(content, "F", 1);
	if (content && is_clean_color(data, 'F') == true)
	{
		(*color_status)++;
		save_color(map, content, 1, error);
		return (*error);
	}
	content = data;
	content = ft_strnstr(content, "C", 1);
	if (content && is_clean_color(data, 'C') == true)
	{
		(*color_status)++;
		save_color(map, content, 2, error);
		return (*error);
	}
	return (2);
}
