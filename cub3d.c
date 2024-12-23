/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:37:11 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 11:12:37 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	init(t_data *data)
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
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->t_img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	checking(ac, av, &game);
	if (!checkmap(&game))
		return (freegamemap(&game), \
		ft_putstr_fd("Error\ninvalid map\n", 1), 1);
	ft_bzero(&data, sizeof(t_data));
	data.my_map = game.map;
	data.ceiling_color = get_hex_color(game.c);
	data.floor_color = get_hex_color(game.f);
	data.game = &game;
	load_player(&data);
	init(&data);
	if (load_wall_texture(&data, &game) == 1)
		close_handler(&data);
	init_event_hooks(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
