/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/09 12:39:29 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	open_file(const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY, 0666);
	if (fd < 0)
	{
		perror("cub3d");
		return (-1);
	}
	return (fd);
}

t_bool	ft_has_spaces_only_cubed(const char *str)
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

void	delete_map(t_map *map, char *data)
{
	if (data)
		free(data);
	// add freeing for textures and colors?
	ft_matrix_delete(&map->content);
}

int	print_content_error(void *str)
{
	if (str)
		free(str);
	ft_putstr_fd("cub3d: ");
	ft_putstr_fd("Invalid file contents\n");
	return (1);
}
