/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:58:50 by ssian             #+#    #+#             */
/*   Updated: 2024/11/07 22:58:52 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/** rotate dir and plane*/
void rotate_player(double *dir_x, double *dir_y, double *plane_x, double *plane_y, double angle_rotate) 
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = *dir_x;
    old_plane_x = *plane_x;
    *dir_x = (old_dir_x * cos(angle_rotate)) - (*dir_y * sin(angle_rotate));
    *dir_y = (old_dir_x * sin(angle_rotate)) + (*dir_y * cos(angle_rotate));
    *plane_x = (old_plane_x * cos(angle_rotate)) - (*plane_y * sin(angle_rotate));
    *plane_y = (old_plane_x * sin(angle_rotate)) + (*plane_y * cos(angle_rotate));
}

/*  check the square the x,y is in is a wall? */
int check_point_in_wall(int x, int y, t_data *data)
{
    int box_x;
    int box_y;

    box_x = x / BOX_HEIGHT;
    box_y = y / BOX_WIDTH;
    if (data->my_map[box_y][box_x] == '1')    
        return (1);
    return (0);
}

void move_front(t_data *data)
{
    if (check_point_in_wall(data->player.pos_x + (data->player.dir_x * (STEPS + FROM_WALL)), data->player.pos_y + (data->player.dir_y * (STEPS + FROM_WALL)), data) == 0)
    {
        data->player.pos_x = data->player.pos_x + (data->player.dir_x * STEPS);
        data->player.pos_y = data->player.pos_y + (data->player.dir_y * STEPS);
    }
}

void move_back(t_data *data)
{
    if (check_point_in_wall(data->player.pos_x - (data->player.dir_x * (STEPS + FROM_WALL)), data->player.pos_y - (data->player.dir_y * (STEPS + FROM_WALL)), data) == 0)
    {
        data->player.pos_x = data->player.pos_x - (data->player.dir_x * STEPS);
        data->player.pos_y = data->player.pos_y - (data->player.dir_y * STEPS);
    }
}

void move_left(t_data *data)
{
    if (check_point_in_wall(data->player.pos_x + (data->player.dir_y * (STEPS + FROM_WALL)), data->player.pos_y - (data->player.dir_x * (STEPS + FROM_WALL)), data) == 0)
    {
        data->player.pos_x = data->player.pos_x + (data->player.dir_y * STEPS);
        data->player.pos_y = data->player.pos_y - (data->player.dir_x * STEPS);
    }
}

void move_right(t_data *data)
{
    if (check_point_in_wall(data->player.pos_x - (data->player.dir_y * (STEPS + FROM_WALL)), data->player.pos_y + (data->player.dir_x * (STEPS + FROM_WALL)), data) == 0)
    {
        data->player.pos_x = data->player.pos_x - (data->player.dir_y * STEPS);
        data->player.pos_y = data->player.pos_y + (data->player.dir_x * STEPS);
    }
}