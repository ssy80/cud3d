/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:52:33 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 14:37:33 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/* select the texture based on the wall side to draw 
   side = 0 is vertical wall(east/west), 
   side = 1 is horizontal wall(north/south)
*/
void	chose_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->chosen_texture = data->ea;
		else
			ray->chosen_texture = data->we;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->chosen_texture = data->so;
		else
			ray->chosen_texture = data->no;
	}
}

/* map wall_x to the texture x coordinate
   Flip horizontally for specific wall
   Flip vertically for another wall*/
static void	get_texture_x(t_ray *ray)
{
	ray->texture_x = (int)(ray->wall_x * (double)ray->chosen_texture.width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;
	if (ray->texture_x < 0)
		ray->texture_x = 0;
	if (ray->texture_x >= ray->chosen_texture.width)
		ray->texture_x = ray->chosen_texture.width - 1;
}

/*top_dist = y - (WINDOW_HEIGHT / 2) + (line_height / 2); 
  Calculate distance from top of the screen
texture_y = (top_dist * chosen_texture.height) / line_height;
  Map y-coordinate to the texture*/
static void	get_texture_y(t_ray *ray, int y)
{
	ray->top_dist = y - (WINDOW_HEIGHT / 2) + (ray->line_height / 2);
	ray->texture_y = (ray->top_dist * ray->chosen_texture.height)
		/ ray->line_height;
	if (ray->texture_y < 0)
		ray->texture_y = 0;
	if (ray->texture_y >= ray->chosen_texture.height)
		ray->texture_y = ray->chosen_texture.height - 1;
}

/* draw the texure wall on screen */
void	draw_texture_wall(t_ray *ray, t_data *data, int x)
{
	int				y;
	char			*pixel;
	unsigned int	color;

	get_texture_x(ray);
	y = ray->draw_start_y;
	while (y < ray->draw_end_y)
	{
		get_texture_y(ray, y);
		pixel = ray->chosen_texture.addr + (ray->texture_y
				* ray->chosen_texture.line_length + ray->texture_x
				* (ray->chosen_texture.bpp / 8));
		color = *(unsigned int *)pixel;
		my_mlx_pixel_put(&(data->t_img), x, y, color);
		y++;
	}
}
