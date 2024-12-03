/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:37:11 by ssian             #+#    #+#             */
/*   Updated: 2024/11/06 14:37:14 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window
		(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	data->t_img.img = mlx_new_image
		(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->t_img.addr = mlx_get_data_addr(data->t_img.img, &data->t_img.bpp,
			&data->t_img.line_len, &data->t_img.endian);
}

int	render(t_data *data)
{
	clear_window(data);

    if(MAP_2D == 1)
    {
        //draw circle of player
        draw_circle(data, data->player.pos_x, data->player.pos_y, PLAYER_RADIUS, 0x000000);
        //draw player direction ray
        draw_line(data, data->player.pos_x, data->player.pos_y, data->player.pos_x + (data->player.dir_x * 20), data->player.pos_y + (data->player.dir_y*20), RED);
    }
    ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->t_img.img, 0, 0);
    return (0);
}


int main(int ac, char **av)
{
    t_data data;
    t_game  game;

    checking(ac, av);
	loadvar(av, &game);
    ft_bzero(&data, sizeof(t_data));
    data.my_map = get_map();
    load_player(&data);
    init(&data);
    load_wall_texture(&data);
	//render(&data);
	// init_event_hooks(&data);
    // mlx_loop_hook(data.mlx, render, &data);
	// mlx_loop(data.mlx);
}