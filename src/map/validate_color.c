/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:41:17 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/28 21:33:53 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_clean_color(char *data, int chr)
{
	int	index;

	index = 0;
	if (data)
	{
		while (data[index] != chr)
		{
			if (data[index] != MAP_SPACE)
				return (false);
			index++;
		}
		return (true);
	}
	return (false);
}

bool	too_many_commas(char *str)
{
	int	index;
	int	commas;

	index = 0;
	commas = 0;
	while (str[index])
	{
		if (str[index] == ',')
			commas++;
		index++;
	}
	if (commas != 2)
		return (true);
	return (false);
}

int	validate_color(char *cleaned_color)
{
	char	*verifier;
	int		overflow;
	int		color;

	verifier = NULL;
	overflow = 0;
	color = (int)ft_atoi(cleaned_color, &overflow);
	verifier = (char *)malloc(sizeof(char) * (ft_strlen(cleaned_color) + 1));
	if (!verifier)
	{
		free(cleaned_color);
		return (-1);
	}
	verifier = ft_itoa((int)color, verifier, 10);
	if (verifier == NULL || overflow == 1 || color < 0 || color > 255
		|| ft_strcmp(cleaned_color, verifier) != 0)
	{
		free(verifier);
		free(cleaned_color);
		return (-1);
	}
	free(verifier);
	free(cleaned_color);
	return (color);
}
