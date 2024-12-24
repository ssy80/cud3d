/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:58:50 by ssian             #+#    #+#             */
/*   Updated: 2024/12/24 11:47:01 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*  check the square the x,y is in is a wall, and 
	to prevent diagonal movoment */
int	check_point_in_wall(int x, int y, t_data *data)
{
	int	box_x;
	int	box_y;
	int	can_move_x;
	int	can_move_y;

	box_x = x / BOX_HEIGHT;
	box_y = y / BOX_WIDTH;
	if (data->my_map[box_y][box_x] == '1')
		return (1);
	else
	{
		can_move_x = (data->my_map[(int)
				(data->player.pos_y / BOX_WIDTH)][box_x] != '1');
		can_move_y = (data->my_map[box_y]
			[(int)(data->player.pos_x) / BOX_HEIGHT] != '1');
		if (can_move_x && can_move_y)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	move_front(t_data *data)
{
	if (check_point_in_wall(data->player.pos_x + (data->player.dir_x
				* (STEPS + FROM_WALL)), data->player.pos_y + (data->player.dir_y
				* (STEPS + FROM_WALL)), data) == 0)
	{
		data->player.pos_x = data->player.pos_x + (data->player.dir_x * STEPS);
		data->player.pos_y = data->player.pos_y + (data->player.dir_y * STEPS);
	}
}

void	move_back(t_data *data)
{
	if (check_point_in_wall(data->player.pos_x - (data->player.dir_x
				* (STEPS + FROM_WALL)), data->player.pos_y
			- (data->player.dir_y * (STEPS + FROM_WALL)), data) == 0)
	{
		data->player.pos_x = data->player.pos_x - (data->player.dir_x * STEPS);
		data->player.pos_y = data->player.pos_y - (data->player.dir_y * STEPS);
	}
}

void	move_left(t_data *data)
{
	if (check_point_in_wall(data->player.pos_x + (data->player.dir_y
				* (STEPS + FROM_WALL)), data->player.pos_y
			- (data->player.dir_x * (STEPS + FROM_WALL)), data) == 0)
	{	
		data->player.pos_x = data->player.pos_x + (data->player.dir_y * STEPS);
		data->player.pos_y = data->player.pos_y - (data->player.dir_x * STEPS);
	}
}

void	move_right(t_data *data)
{
	if (check_point_in_wall(data->player.pos_x - (data->player.dir_y
				* (STEPS + FROM_WALL)), data->player.pos_y
			+ (data->player.dir_x * (STEPS + FROM_WALL)), data) == 0)
	{
		data->player.pos_x = data->player.pos_x - (data->player.dir_y * STEPS);
		data->player.pos_y = data->player.pos_y + (data->player.dir_x * STEPS);
	}
}
