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
void	findstartpos(t_game *game, int *coor)
{
	int	r;
	int	c;

	r = -1;
	coor[0] = -1;
	coor[1] = -1;
	while (game->map[++r])
	{
		c = -1;
		while (game->map[r][++c])
		{
			if (game->map[r][c] == 'N' || game->map[r][c] == 'S' || \
			game->map[r][c] == 'E' || game->map[r][c] == 'W')
			{
				coor[0] = r;
				coor[1] = c;
				break ;
			}
		}
	}
}

// depth first search for space and out of map
bool	dfs(t_game *game, bool visit[2000][2000], int r, int c)
{
	if (visit[r][c] || game->map[r][c] == '1')
		return (false);
	if (r < 0 || c < 0 || r >= game->row \
	|| c >= game->col || game->map[r][c] == ' ')
		return (true);
	visit[r][c] = true;
	return (dfs(game, visit, r + 1, c) || dfs(game, visit, r - 1, c) \
	|| dfs(game, visit, r, c + 1) || dfs(game, visit, r, c - 1));
}

// check that map is enclosed
bool	validmap(t_game *game, int lr, int lc)
{
	bool	visit[2000][2000];
	int		pos[2];

	ft_bzero(visit, sizeof(bool) * 2000 * 2000);
	if (lr > 2000 || lc > 2000)
		return (ft_putstr_fd("map too big\n", 1), false);
	findstartpos(game, pos);
	return (!dfs(game, visit, pos[0], pos[1]));
}

// check that 3 color values are within 0 - 255 
bool	checkcolor(char **tmp, int id, int c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (tmp[id][i])
	{
		j = 0;
		n = 0;
		while (tmp[id][j + i] && tmp[id][j + i] != ',')
			if (ft_isdigit(tmp[id][i + j++]))
				n++;
		if (n <= 0 || n > 3)
			return (false);
		if (tmp[id][i + j] == ',')
			c++;
		if (j > 0)
			i += j + 1;
		else
			i++;
	}
	if (c != 2 || tmp[id][i - 1] == ',' || tmp[id][i - 1] == ' ')
		return (false);
	return (true);
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
	if (j > 0)
		return (false);
	return (true);
}
