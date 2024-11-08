/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:15:43 by yoong             #+#    #+#             */
/*   Updated: 2024/11/08 23:15:45 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	key_down(int keycode, t_player *player)
{
	if (keycode == XK_w)
		player->up = true;
	if (keycode == XK_s)
		player->down = true;
	if (keycode == XK_a)
		player->left = true;
	if (keycode == XK_d)
		player->right = true;
	if (keycode == XK_Left)
		player->rleft = true;
	if (keycode == XK_Right)
		player->rright = true;
	return (0);
}

int	key_up(int keycode, t_player *player)
{
	if (keycode == XK_w)
		player->up = false;
	if (keycode == XK_s)
		player->down = false;
	if (keycode == XK_a)
		player->left = false;
	if (keycode == XK_d)
		player->right = false;
	if (keycode == XK_Left)
		player->rleft = false;
	if (keycode == XK_Right)
		player->rright = false;
	return (0);
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->up = false;
	player->down = false;
	player->right = false;
	player->left = false;
	player->rleft = false;
	player->rright = false;
}
