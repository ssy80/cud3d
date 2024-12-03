/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:18:14 by yoong             #+#    #+#             */
/*   Updated: 2024/12/03 11:18:31 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

void	freesplit(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

void	freetmparr(char **tmp)
{
	int	i;

	i = -1;
	while (++i < 6)
		free(tmp[i]);
}

void	freegamemap(t_game *game)
{
	int	i;

	i = -1;
	while (game->map[++i])
		free(game->map[i]);
	free(game->map);
}
