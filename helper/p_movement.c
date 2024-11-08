/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:11:34 by yoong             #+#    #+#             */
/*   Updated: 2024/11/09 00:11:53 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	p_up(t_player *player, float cos_ng, float sin_ng, int sp)
{
	player->x += cos_ng * sp;
	player->y += sin_ng * sp;
}

static void	p_down(t_player *player, float cos_ng, float sin_ng, int sp)
{
	player->x -= cos_ng * sp;
	player->y -= sin_ng * sp;
}

static void	p_left(t_player *player, float cos_ng, float sin_ng, int sp)
{
	player->x += sin_ng * sp;
	player->y -= cos_ng * sp;
}

static void	p_right(t_player *player, float cos_ng, float sin_ng, int sp)
{
	player->x -= sin_ng * sp;
	player->y += cos_ng * sp;
}

void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	angle_speed = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->rleft)
		player->angle -= angle_speed;
	if (player->rright)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->up)
		p_up(player, cos_angle, sin_angle, speed);
	if (player->down)
		p_down(player, cos_angle, sin_angle, speed);
	if (player->left)
		p_left(player, cos_angle, sin_angle, speed);
	if (player->right)
		p_right(player, cos_angle, sin_angle, speed);
}
