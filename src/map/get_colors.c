/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:47:03 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/09 12:49:26 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	verify_colors(int *colors, char **color)
{
	colors[0] = ft_atoi(color[0]);
	if (colors[0] < 0 || colors[0] > 255)
	{
		ft_matrix_delete(&color);
		return (print_content_error(colors));
	}
	colors[1] = ft_atoi(color[1]);
	if (colors[1] < 0 || colors[1] > 255)
	{
		ft_matrix_delete(&color);
		return (print_content_error(colors));
	}
	colors[2] = ft_atoi(color[2]);
	if (colors[2] < 0 || colors[2] > 255)
	{
		ft_matrix_delete(&color);
		return (print_content_error(colors));
	}
	return (0);
}

static int	copy_colors(t_map *specs, int *colors, char **color, int id)
{
	if (verify_colors(colors, color) > 0)
		return (1);
	ft_matrix_delete(&color);
	if (id == 1 && specs->f)
		return (print_content_error(colors));
	else if (id == 1 && !specs->f)
		specs->f = colors;
	else if (id == 2 && specs->c)
		return (print_content_error(colors));
	else if (id == 2 && !specs->c)
		specs->c = colors;
	return (0);
}

static int	extract_clor(t_map *specs, char *line, int identifier)
{
	char	*extract;
	char	**color;
	int		*colors;

	extract = ft_strtrim(line + 1, " ");
	if (!extract) // print error?
		return (1);
	color = ft_split(extract, ',');
	if (!color)
		return (print_content_error(extract)); // what if malloc fails in split??
	free(extract);
	if (ft_matrix_count_rows(color) != 3)
	{
		ft_matrix_delete(&color);
		return (print_content_error(NULL));
	}
	colors = (int *)malloc(sizeof(int) * 3);
	if (!colors)
	{
		ft_matrix_delete(&color);
		return (1);
	}
	return (copy_colors(specs, colors, color, identifier));
}

int	get_color(t_map *specs, char *data)
{
	char	*content;
	
	if (specs->no && specs->so && specs->we && specs->ea)
	{
		content = data;
		if (ft_strnstr(content, "F", 1))
			return (extract_color(specs, content, 1));
		content = data;
		if (ft_strnstr(content, "C", 1))
			return (extract_color(specs, content, 1));
	}
	return (print_content_error(NULL));
}
