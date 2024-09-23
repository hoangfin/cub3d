/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:33:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 23:06:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

/**
 * Return a color which is defined by `rgba` value.
 */
uint32_t	color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
