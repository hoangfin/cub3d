/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:52:15 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/09 12:52:58 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	verify_fileformat(char *filename, char *filetype)
{
	size_t		length;

	length = ft_strlen(filename);
	return (ft_strncmp(&file[length - 4], filetype, 4));
}

static int	check_file(char *filename) // add dir check?
{
	int	fd;
	
	if (verify_fileformat(filename, ".cub") != 0)
	{
		ft_putstr_fd("cub3d: ");
		ft_putstr_fd("Invalid file format\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{
		perror("cub3d");
		return (-1);
	}
	return (fd);
}

bool	validate(int argc, char **argv)
{
	int	fd;
	
	if (argc != 2 || argv[1] == NULL || argv[1][0] == '\0')
		return (false);
	fd = check_file(filename);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}
