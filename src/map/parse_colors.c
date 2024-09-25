/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/25 17:18:39 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int32_t	color_check(char *color_data)
{
	int		overflow;
	int32_t	color;
	char	*verifier;
	char	*trimmed_color;

	verifier = NULL;
	trimmed_color = ft_strtrim(color_data, " ");
	if (!trimmed_color || ft_strcmp(trimmed_color, "\0") == 0)
	{
		if (trimmed_color)
			free(trimmed_color);
		return (-1);
	}
	overflow = 0;
	color = (int32_t)ft_atoi(trimmed_color, &overflow);
	verifier = (char *)malloc(sizeof(char) * (ft_strlen(trimmed_color) + 1));
	if (!verifier)
	{
		free(trimmed_color);
		return (-1);
	}
	verifier = ft_itoa((int)color, verifier, 10);
	if (verifier == NULL || overflow == 1 || color < 0 || color > 255
		|| ft_strcmp(trimmed_color, verifier) != 0)
	{
		free(verifier);
		free(trimmed_color);
		return (-1);
	}
	free(verifier);
	free(trimmed_color);
	return (color);
}

static void	verify_colors(t_map *map, char **colors, int id, int *error)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;

	red = color_check(colors[0]);
	green = color_check(colors[1]);
	blue = color_check(colors[2]);
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

int	get_color(t_map *map, char *data, int *error, int *color_status)
{
	char	*content;

	content = data;
	content = ft_strnstr(content, "F", 1);
	if (content)
	{
		(*color_status)++;
		save_color(map, content, 1, error);
		return (*error);
	}
	content = data;
	content = ft_strnstr(content, "C", 1);
	if (content)
	{
		(*color_status)++;
		save_color(map, content, 2, error);
		return (*error);
	}
	return (2);
}
