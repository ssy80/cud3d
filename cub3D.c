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
	game->data = mlx_get_data_addr(game->img_ptr, &game->bpp, \
	&game->size_line, &game->endian);
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

int	char2dlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int parseint(char *s, int *i, int n)
{
	if (s[*i] && ft_isdigit(s[*i]))
		return ((*i)++, parseint(s, i, n * 10 + (s[*i - 1] - '0')));
	if (n > 255)
		return (-1);
	return (n);
}

void	freetmparr(char **tmp)
{
	int	i;

	i = -1;
	while (++i < 6)
		free(tmp[i]);
}

void loadfc(t_game *game, char **tmp, int fc)
{
	int		i;
	int		j;
	int		comma;
	char	*s;

	i = -1;
	j = -1;
	comma = 0;
	s = tmp[fc];
	while (s[++i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r')
			continue;
		if (ft_isdigit(s[i]) && j <2 && fc == FLOOR)
			game->f[++j] = parseint(s, &i, 0);
		if (ft_isdigit(s[i]) && j <2 && fc == CEIL)
			game->c[++j] = parseint(s, &i, 0);
		if (s[i] == ',' && ++comma >= 0)
			continue;
	}
}

bool	checkcolor(char **tmp, int id, int c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (tmp[id][i])
	{
		j = 0;
		n = 0;
		while (tmp[id][j + i] && tmp[id][j + i] != ',')
			if (ft_isdigit(tmp[id][i + j++]))
				n++;
		if (n <= 0 || n > 3)
			return (false);
		if (tmp[id][i + j] == ',')
			c++;
		if (j > 0)
			i += j + 1;
		else
			i++;
	}
	if (c != 2 || tmp[id][i-1] == ',' || tmp[id][i-1] == ' ')
		return (false);
	return (true);
}

void loadpath(t_game *game, char **tmp)
{
	game->n = tmp[NTH];
	game->s = tmp[STH];
	game->e = tmp[EST];
	game->w = tmp[WST];
	ft_bzero(game->f, sizeof(int) * 3);
	ft_bzero(game->c, sizeof(int) * 3);
	if (!checkcolor(tmp, FLOOR, 0) || !checkcolor(tmp, CEIL, 0))
		return (ft_putstr_fd("Error in color\n", 1), freetmparr(tmp), \
		smart_ptr(NULL, FREE) ,exit(1));
	loadfc(game, tmp, FLOOR);
	loadfc(game, tmp, CEIL);
}

void loadvar(char *av[], t_game *game)
{
	char	**ss;
	int		i;
	char	*tmp[6];
	char	**paths;

	ft_bzero(tmp, sizeof(char*) * 6);
	ss = openfile(av[1]);
	if (!ss)
		return (ft_putstr_fd("Error FileProb\n", STDOUT_FILENO), exit(1));
	i = -1;
	while (++i < 6)
	{
		paths = ft_split(ss[i], ' ');
		if (!paths)
			return (ft_putstr_fd("Error MallocErr\n", 1), freesplit(ss), exit(1));
		if (char2dlen(paths) != 2)
			return (ft_putstr_fd("Error BlankProb\n", 1), freesplit(paths), freesplit(ss), exit(1));
		tmp[identify(ss[i])] = ft_calloc(ft_strlen(paths[1]) + 2, sizeof(char));
		if (!tmp[identify(ss[i])])
			return (ft_putstr_fd("Error 292\n", 1), freesplit(paths), freesplit(ss), exit(1));
		ft_memcpy(tmp[identify(ss[i])], paths[1], ft_strlen(paths[1]));
		freesplit(paths);
	}
	return (freesplit(ss), loadpath(game, tmp));
}

int	main(int ac, char *av[])
{
	t_game	game;

	checking(ac, av);
	loadvar(av, &game);
	// init_game(&game);
	// mlx_hook(game.win_ptr, 2, 1L << 0, key_down, &game.player);
	// mlx_hook(game.win_ptr, 3, 1L << 1, key_up, &game.player);
	// draw_square(&game, WIDTH / 2, HEIGHT / 2, 10, 0x00FF00);
	// mlx_loop_hook(game.mlx_ptr, draw_loop, &game);
	// mlx_loop(game.mlx_ptr);
	return (0);
}
