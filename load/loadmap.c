/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:32:53 by yoong             #+#    #+#             */
/*   Updated: 2024/12/02 23:33:02 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

static void	delnextline(char *str)
{
	int	l;

	if (!str)
		return ;
	l = ft_strlen(str);
	if (str[l - 1] == '\n')
		str[l - 1] = '\0';
}

void	gamevar(t_game *game)
{
	int	i;

	i = -1;
	delnextline(game->n);
	delnextline(game->s);
	delnextline(game->w);
	delnextline(game->e);
	while (++i < game->row)
		delnextline(game->map[i]);
}

bool	loadmap(t_game *game, char **ss)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (ss[++i])
		j = max(ft_strlen(ss[i]), j);
	game->map = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (ss[++i])
	{
		game->map[i] = ft_calloc(j + 1, sizeof(char));
		ft_memcpy(game->map[i], ss[i], ft_strlen(ss[i]));
	}
	game->row = i;
	game->col = j;
	if (!checkmap(game) || !validmap(game, i, j))
		return (false);
	return (true);
}

void	loadcheckmap(t_game *game, char	**ss, char **tmp)
{
	if (loadmap(game, ss + 6))
		return ;
	freesplit(ss);
	freegamemap(game);
	freetmparr(tmp);
	ft_putstr_fd("Error in map\n", 1);
	smart_ptr(NULL, FREE);
	exit(1);
}
