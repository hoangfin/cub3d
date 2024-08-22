/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/22 09:28:15 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

t_bool	ft_has_spaces_only_cubed(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	print_content_error(void *str, double i, int *error)
{
	if (str)
		free(str);
	if (error)
		*error = 1;
	printf("error id: %f\n", i);
	write(STDERR_FILENO, "Error\nInvalid map file contents\n", 32);
	return (1);
}

void	copy_line(t_map *map, char *line, unsigned int index)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i] && line[i] != '\n')
		{
			map->grid[index][i] = line[i];
			i++;
		}
		map->grid[index][i] = '\0';
	}
}

int	map_edge(char *line)
{
	int	index;

	index = 0;
	while (line[index] && line[index] != '\n')
	{
		if (line[index] != MAP_WALL && line[index] != MAP_SPACE)
			return (1);
		index++;
	}
	return (0);
}

int	check_file_end(int fd)
{
	int		status;
	char	*line;

	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, "\n") != 0 && !ft_has_spaces_only_cubed(line))
		{
			free(line);
			return (1);
		}
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	return (0);
}
