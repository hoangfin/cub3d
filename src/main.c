/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/08 22:21:07 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	has_valid_args(int argc, const char *pathname)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Invalid number of arguments", STDERR_FILENO);
		return (false);
	}
	if (ft_ends_with(pathname, ".cub") == false)
	{
		ft_putendl_fd("Error: map file must end with '.cub'", STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_cub3D	cub3D;

	if (
		has_valid_args(argc, argv[1]) == false
		|| init(&cub3D, argv[1]) != 0
		|| start(&cub3D) != 0
	)
		return (EXIT_FAILURE);
	destroy(&cub3D);
	return (EXIT_SUCCESS);
}
