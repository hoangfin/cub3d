/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:52:15 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 10:12:46 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "cub3D.h"

int	check_file_permissions(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd > -1)
	{
		write(STDERR_FILENO, "Error\n", 6);
		ft_putstr_fd(file, STDERR_FILENO);
		write(STDERR_FILENO, " is a directory\n", 16);
		close(fd);
		return (-1);
	}
	fd = open(file, O_RDONLY, 0666);
	if (fd < 0)
	{
		write(STDERR_FILENO, "Error\nCannot open ", 18);
		ft_putendl_fd(file, STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

int	verify_fileformat(char *filename, char *filetype)
{
	size_t		length;

	length = ft_strlen(filename);
	return (ft_strncmp(&filename[length - 4], filetype, 4));
}

int	validate(char *map_file)
{
	if (map_file[0] == '\0' || verify_fileformat(map_file, ".cub") != 0)
	{
		write(STDERR_FILENO, "Error\nInvalid map file format\n", 30);
		return (-1);
	}
	return (check_file_permissions(map_file));
}
