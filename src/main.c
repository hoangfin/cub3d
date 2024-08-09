/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/09 14:33:47 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D	cub3D;
	
	(void)argc;
	if (init(&cub3D, argv[1]) != 0 || start(&cub3D) != 0)
		return (EXIT_FAILURE);
	destroy(&cub3D);
	return (EXIT_SUCCESS);
}
