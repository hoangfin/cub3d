/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 10:53:32 by emansoor         ###   ########.fr       */
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

int	print_content_error(void *str, double i)
{
	if (str)
		free(str);
	printf("error id: %f\n", i);
	write(STDERR_FILENO, "Error\nInvalid map file contents\n", 32);
	return (1);
}
