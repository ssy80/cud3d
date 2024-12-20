/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:59:06 by ssian             #+#    #+#             */
/*   Updated: 2024/12/20 13:38:20 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*'W' = 0*/
double	get_plane_x(char dir)
{
	if (dir == 'N')
		return (0.66);
	else if (dir == 'S')
		return (-0.66);
	else if (dir == 'E')
		return (0);
	else
		return (0);
}

/*'W' = -0.66*/
double	get_plane_y(char dir)
{
	if (dir == 'N')
		return (0);
	else if (dir == 'S')
		return (0);
	else if (dir == 'E')
		return (0.66);
	else
		return (-0.66);
}
