/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:33:52 by ssian             #+#    #+#             */
/*   Updated: 2024/11/07 20:33:55 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


/* draw a line */
void    draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
    double delta_x;
    double delta_y;
    int pixels;
    double pixel_x;
    double pixel_y;

    delta_x = end_x - start_x;
    delta_y = end_y - start_y;
    pixels = 0;
    pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
    delta_x = delta_x / pixels;
    delta_y = delta_y / pixels;
    pixel_x = start_x;
    pixel_y = start_y;
    while (pixels > 0)
    {
        my_mlx_pixel_put(&(data->t_img), pixel_x, pixel_y, color);
        pixel_x = pixel_x + delta_x;
        pixel_y = pixel_y + delta_y;
        pixels--;
    }
}

void draw_circle(t_data *data, int start_x, int start_y, int radius, int color) 
{
    int x;
    int y;

    x = 0;
    y = -radius;
    
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if ((x * x + y * y) <= (radius * radius)) 
                my_mlx_pixel_put(&(data->t_img), (start_x + x), (start_y + y), color);
            x++;
        }
        y++;
    }
}

/* draw 2d map*/
void draw_point_map(int x, int y, t_data *data)
{
    int box_x = x / BOX_WIDTH;
    int box_y = y / BOX_HEIGHT;

    if (data->my_map[box_y][box_x] == '1')
        my_mlx_pixel_put(&(data->t_img), x, y, GRAY);
    else if (data->my_map[box_y][box_x] == '0')
        my_mlx_pixel_put(&(data->t_img), x, y, WHITE);
    else if (data->my_map[box_y][box_x] == 'N' || data->my_map[box_y][box_x] == 'S' || data->my_map[box_y][box_x] == 'E' || data->my_map[box_y][box_x] == 'W')
        my_mlx_pixel_put(&(data->t_img), x, y, GREEN);
}

/* clear screen*/
void clear_window(t_data *data)
{
    int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
            if(MAP_2D == 1)
                draw_point_map(x, y, data);
            else
                my_mlx_pixel_put(&(data->t_img), x, y, WHITE);
			x++;
		}
		y++;
	}
}