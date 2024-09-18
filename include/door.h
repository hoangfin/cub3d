/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:04 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/18 11:56:09 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPEN,
	DOOR_CLOSING,
	DOOR_OPENING
}	t_door_state;

