/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:52:25 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 14:29:09 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*init a ray for every pixel(x) of the screen width.*/
void	ray_setup(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->pos_x = data->player.pos_x / BOX_WIDTH;
	ray->pos_y = data->player.pos_y / BOX_HEIGHT;
	ray->box_x = (int)ray->pos_x;
	ray->box_y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* calculate init step direction and side dist with delta_dist*/
void	calculate_step_side_dist(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->box_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->box_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->box_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->box_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

/* perform DDA, stop when wall hit */
/* jump to the next map square, either in x-direction or y-direction 
   side 0 = vertical side hit, 1 = horizontal side hit
   calculate the perpendicular distance to the wall to avoid the fish-eye effect
*/
void	perform_dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
			ray->box_x = ray->box_x + ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
			ray->box_y = ray->box_y + ray->step_y;
			ray->side = 1;
		}
		if (data->my_map[ray->box_y][ray->box_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

/* calculate height of the line, start_y, end_y points to draw. 
   calculate the start and end positions of the line */
void	calculate_line_height(t_ray *ray)
{
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start_y = (-ray->line_height / 2) + (WINDOW_HEIGHT / 2);
	if (ray->draw_start_y < 0)
		ray->draw_start_y = 0;
	ray->draw_end_y = (ray->line_height / 2) + (WINDOW_HEIGHT / 2);
	if (ray->draw_end_y >= WINDOW_HEIGHT)
		ray->draw_end_y = WINDOW_HEIGHT - 1;
}

/* calculate the x point hit on the wall, exact point of intersection
	between the ray and the wall,
   Note that even if it's called wall_x, it's actually an
	y-coordinate of the wall if side==1,
   but it's always the x-coordinate of the texture.
*/
void	calculate_wall_hit(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
}
