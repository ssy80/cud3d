/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:30:18 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 14:30:34 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	index = y * game->size_line + x * game->bpp / 8;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	game->data[index] = color & 255;
	game->data[index + 1] = (color >> 8) & 255;
	game->data[index + 2] = (color >> 16) & 255;
}

// our own clear_image
void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(game, x, y, 0);
	}
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img_ptr, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
}

// distance calculation functions
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

// utils functions
void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(game, x + i, y, color);
	i = -1;
	while (++i < size)
		put_pixel(game, x, y + i, color);
	i = -1;
	while (++i < size)
		put_pixel(game, x + size, y + i, color);
	i = -1;
	while (++i < size)
		put_pixel(game, x + i, y + size, color);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

// raycasting functions
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(game, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(game, i, start_y, 255);
			start_y++;
		}
	}
}


void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x0000FF;
	y = -1;
	while (map[++y]){
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, color);
	}
}

int	draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	if (DEBUG)
	{
		draw_square(game, player->x, player->y, 10, 0x00FF00);
		draw_map(game);
	}
	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	game;

	checking(ac, av);
	init_game(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_down, &game.player);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_up, &game.player);
	draw_square(&game, WIDTH / 2, HEIGHT / 2, 10, 0x00FF00);
	mlx_loop_hook(game.mlx_ptr, draw_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
