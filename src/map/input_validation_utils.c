/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 09:34:18 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	print_content_error(void *str)
{
	if (str)
		free(str);
	write(STDERR_FILENO, "Error\nInvalid file contents\n", 28);
	return (1);
}
