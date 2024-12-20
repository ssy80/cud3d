/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:11:47 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 11:14:17 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_event_hooks(t_data *data)
{
	mlx_hook((data->win), KeyPress, KeyPressMask, key_handler, data);
	mlx_hook((data->win), DestroyNotify,
		StructureNotifyMask, close_handler, data);
}

/** angle rotate is in radians */
int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_handler(data);
	else if (keycode == XK_w)
		move_front(data);
	else if (keycode == XK_s)
		move_back(data);
	else if (keycode == XK_a)
		move_left(data);
	else if (keycode == XK_d)
		move_right(data);
	else if (keycode == XK_Left)
		rotate_player_left(&(data->player.dir_x), &(data->player.dir_y),
			&(data->player.plane_x), &(data->player.plane_y));
	else if (keycode == XK_Right)
		rotate_player_right(&(data->player.dir_x), &(data->player.dir_y),
			&(data->player.plane_x), &(data->player.plane_y));
	return (0);
}

int	close_handler(t_data *data)
{
	free_textures(data);
	mlx_destroy_image(data->mlx, data->t_img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	freegamemap(data->game);
	exit (0);
}
