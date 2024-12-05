/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:56:58 by yoong             #+#    #+#             */
/*   Updated: 2024/12/04 19:57:02 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

bool	checkcolorval(char **tmp, int id)
{
  int	i;
	int	n;

	i = -1;
	n = 0;
	while (tmp[id][++i])
		if (tmp[id][i] == ' ')
			continue;
		else
			break;
	while (tmp[id][++i])
	{
		if (tmp[id][i] == ',')
			n++;
		if (ft_isdigit(tmp[id][i]) || tmp[id][i] == ',')
			continue;
		return (false);
	}
	if (n != 2)
		return (false);
	return (true);
}
