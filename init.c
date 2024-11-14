/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:29:57 by ssian             #+#    #+#             */
/*   Updated: 2024/11/12 11:29:59 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"



char **get_map()
{
	char	**map = malloc(sizeof(char *) * 15);

	map[0] = "000000001111111111111111111111111";
	map[1] = "000000001000000000110000000000001";
	map[2] = "000000001011000001110000000000001";
    map[3] = "000000001001000000000000000000001";
	map[4] = "111111111011000001110000000000001";
	map[5] = "100000000011000001110111111111111";
	map[6] = "111101111111110111000000100010000";
	map[7] = "111101111111110111010100100010000";
	map[8] = "110000001101010111000000100010000";
	map[9] = "100000000000000011000000000010000";
	map[10] = "100000000000000011010100100010000";
    map[11] = "11000001110101011111011110N011100";
    map[12] = "111101110111010101011110100010000";
    map[13] = "111111110111111101111111111110000";
	map[14] = NULL;
	return (map);
}

void load_player(t_data *data)
{
    char **my_map;
    int x;
    int y;

    my_map = data->my_map;

    y = 0;
    while (my_map[y])
    {
        x = 0;
        while (my_map[y][x])
        {
            if (my_map[y][x] == 'N' || my_map[y][x] == 'S' || my_map[y][x] == 'E' || my_map[y][x] == 'W')
            {
                data->player.pos_x = get_player_pos_x(x);      //change to location in  window
                data->player.pos_y = get_player_pos_y(y);      //change to location in  window
                data->player.dir_x = get_player_dir_x(my_map[y][x]);
                data->player.dir_y = get_player_dir_y(my_map[y][x]);
                data->player.plane_x = get_plane_x(my_map[y][x]);
                data->player.plane_y = get_plane_y(my_map[y][x]);
            }
            x++;
        }
        y++;
    }
}

void load_wall_texture(t_data *data)
{
    char *no_path = "./pics/redbrick.xpm"; 
    char *so_path = "./pics/eagle.xpm"; 
    char *we_path = "./pics/bluestone.xpm"; 
    char *ea_path = "./pics/wood.xpm"; 
    data->no = load_texture(data->mlx, no_path);
    data->so = load_texture(data->mlx, so_path);
    data->we = load_texture(data->mlx, we_path);
    data->ea = load_texture(data->mlx, ea_path);
}