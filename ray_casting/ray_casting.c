/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:31:35 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 14:09:50 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*init dir, camera plane vector(x,y)*/
static void	ray_init(t_ray *ray, t_data *data)
{
	ray->dir_x = data->player.dir_x;
	ray->dir_y = data->player.dir_y;
	ray->plane_x = data->player.plane_x;
	ray->plane_y = data->player.plane_y;
}

void	ray_casting(t_data *data)
{
	int		x;
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray_init(&ray, data);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_setup(&ray, data, x);
		calculate_step_side_dist(&ray);
		perform_dda(&ray, data);
		calculate_line_height(&ray);
		calculate_wall_hit(&ray);
		chose_texture(&ray, data);
		draw_texture_wall(&ray, data, x);
		draw_ceiling(&ray, data, x);
		draw_floor(&ray, data, x);
		x++;
	}
}
