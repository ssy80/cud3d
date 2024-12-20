/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:12:40 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 13:55:07 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/** rotate dir and plane*/
void	rotate_player_left(double *dir_x, double *dir_y,
		double *plane_x, double *plane_y)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = *dir_x;
	old_plane_x = *plane_x;
	*dir_x = (old_dir_x * cos(-ANGLE_ROTATE)) - (*dir_y * sin(-ANGLE_ROTATE));
	*dir_y = (old_dir_x * sin(-ANGLE_ROTATE)) + (*dir_y * cos(-ANGLE_ROTATE));
	*plane_x = (old_plane_x * cos(-ANGLE_ROTATE))
		- (*plane_y * sin(-ANGLE_ROTATE));
	*plane_y = (old_plane_x * sin(-ANGLE_ROTATE))
		+ (*plane_y * cos(-ANGLE_ROTATE));
}

void	rotate_player_right(double *dir_x, double *dir_y,
		double *plane_x, double *plane_y)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = *dir_x;
	old_plane_x = *plane_x;
	*dir_x = (old_dir_x * cos(ANGLE_ROTATE)) - (*dir_y * sin(ANGLE_ROTATE));
	*dir_y = (old_dir_x * sin(ANGLE_ROTATE))
		+ (*dir_y * cos(ANGLE_ROTATE));
	*plane_x = (old_plane_x * cos(ANGLE_ROTATE))
		- (*plane_y * sin(ANGLE_ROTATE));
	*plane_y = (old_plane_x * sin(ANGLE_ROTATE))
		+ (*plane_y * cos(ANGLE_ROTATE));
}
