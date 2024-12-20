/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:29:57 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 13:36:46 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*determine the starting pos, dir, camera plane of player*/
void	load_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->my_map[y])
	{
		x = 0;
		while (data->my_map[y][x])
		{
			if (data->my_map[y][x] == 'N' || data->my_map[y][x] == 'S'
					|| data->my_map[y][x] == 'E' || data->my_map[y][x] == 'W')
			{
				data->player.pos_x = get_player_pos_x(x);
				data->player.pos_y = get_player_pos_y(y);
				data->player.dir_x = get_player_dir_x(data->my_map[y][x]);
				data->player.dir_y = get_player_dir_y(data->my_map[y][x]);
				data->player.plane_x = get_plane_x(data->my_map[y][x]);
				data->player.plane_y = get_plane_y(data->my_map[y][x]);
			}
			x++;
		}
		y++;
	}
}

/*return (1) if error loading texture file */
int	load_wall_texture(t_data *data, t_game *game)
{
	data->no = load_texture(data->mlx, game->n);
	data->so = load_texture(data->mlx, game->s);
	data->we = load_texture(data->mlx, game->w);
	data->ea = load_texture(data->mlx, game->e);
	if (data->no.img == NULL || data->so.img == NULL
		|| data->we.img == NULL || data->ea.img == NULL)
		return (1);
	return (0);
}
