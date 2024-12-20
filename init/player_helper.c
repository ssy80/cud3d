/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:25:22 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 13:39:31 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*get x in center of start box*/
int	get_player_pos_x(int box_x)
{
	int	x;

	x = (box_x * BOX_HEIGHT) + (BOX_HEIGHT / 2);
	return (x);
}

/*get y in center of start box*/
int	get_player_pos_y(int box_y)
{
	int	y;

	y = (box_y * BOX_WIDTH) + (BOX_WIDTH / 2);
	return (y);
}

/*'W' = -1*/
int	get_player_dir_x(char facing)
{
	if (facing == 'N')
		return (0);
	else if (facing == 'S')
		return (0);
	else if (facing == 'E')
		return (+1);
	else
		return (-1);
}

/*'W' = 0*/
int	get_player_dir_y(char facing)
{
	if (facing == 'N')
		return (-1);
	else if (facing == 'S')
		return (+1);
	else if (facing == 'E')
		return (0);
	else
		return (0);
}
