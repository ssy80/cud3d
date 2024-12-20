/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:57:02 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 14:38:34 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	draw_ceiling(t_ray *ray, t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start_y)
	{
		my_mlx_pixel_put(&(data->t_img), x, y, data->ceiling_color);
		y++;
	}
}

void	draw_floor(t_ray *ray, t_data *data, int x)
{
	int	y;

	y = ray->draw_end_y;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&(data->t_img), x, y, data->floor_color);
		y++;
	}
}
