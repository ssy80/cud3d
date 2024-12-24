/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mapcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:33:25 by yoong             #+#    #+#             */
/*   Updated: 2024/12/02 23:33:29 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

// find starting pos(to be used after ensuring that map is valid)
void	findstartpos(t_game *game)
{
	int	r;
	int	c;

	r = -1;
	while (game->map[++r])
	{
		c = -1;
		while (game->map[r][++c])
		{
			if (game->map[r][c] == 'N' || game->map[r][c] == 'S' || \
			game->map[r][c] == 'E' || game->map[r][c] == 'W')
			{
				game->pr = r;
				game->pc = c;
				break ;
			}
		}
	}
}

// depth first search for space and out of map
bool	dfs(t_game *game, bool **visit, int r, int c)
{
	if (r < 0 || c < 0 || r >= game->row \
	|| c >= game->col || game->map[r][c] == ' ')
		return (true);
	if (visit[r][c] || game->map[r][c] == '1')
		return (false);
	visit[r][c] = true;
	return (dfs(game, visit, r + 1, c) || dfs(game, visit, r - 1, c) \
	|| dfs(game, visit, r, c + 1) || dfs(game, visit, r, c - 1));
}

// check that map is enclosed
bool	validmap(t_game *game)
{
	bool	**visit;
	int		r;
	int		c;
	int		i;

	i = -1;
	visit = ft_calloc(2001, sizeof(bool *));
	while (++i < 2001)
		visit[i] = ft_calloc(2001, sizeof(bool));
	if (game->row > 2000 || game->col > 2000)
		return (ft_putstr_fd("map too big\n", 1), false);
	findstartpos(game);
	if (dfs(game, visit, game->pr, game->pc))
		return (false);
	r = -1;
	while (++r < game->row)
	{
		c = -1;
		while (++c < game->col)
			if (!visit[r][c] && game->map[r][c] == '0')
				if (dfs(game, visit, r, c))
					return (freeboolean(visit), false);
	}
	return (freeboolean(visit), true);
}

// check map for wrong character
bool	checkmap(t_game *game)
{
	int	i;
	int	j;
	int	in[128];

	i = -1;
	ft_bzero(in, sizeof(int) * 128);
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			in[(int) game->map[i][j]]++;
	}
	if (in['N'] + in['S'] + in['E'] + in['W'] != 1)
		return (false);
	i = -1;
	j = 0;
	while (++i < 128)
		if (i != ' ' && i != '1' && i != '0' && i != 'N' \
		&& i != 'S' && i != 'E' && i != 'W' && i != '\n')
			j += in[i];
	if (j > 0 || !validmap(game))
		return (freegamemap(game), \
		ft_putstr_fd("error\ninvalid map\n", 1), exit(1), false);
	return (true);
}
