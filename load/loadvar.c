/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:47:59 by yoong             #+#    #+#             */
/*   Updated: 2024/12/03 10:48:04 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

int	parseint(char *s, int *i, int n)
{
	if (s[*i] && ft_isdigit(s[*i]))
		return ((*i)++, parseint(s, i, n * 10 + (s[*i - 1] - '0')));
	if (n > 255)
		return (-1);
	return (n);
}

void	loadfc(t_game *game, char **tmp, int fc)
{
	int		i;
	int		j;
	int		comma;
	char	*s;

	i = -1;
	j = -1;
	comma = 0;
	s = tmp[fc];
	while (s[++i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r')
			continue ;
		if (ft_isdigit(s[i]) && j < 2 && fc == FLOOR)
			game->f[++j] = parseint(s, &i, 0);
		if (ft_isdigit(s[i]) && j < 2 && fc == CEIL)
			game->c[++j] = parseint(s, &i, 0);
		if (s[i] == ',' && ++comma >= 0)
			continue ;
	}
}

void	loadpath(t_game *game, char **tmp)
{
	int	i;

	game->n = tmp[NTH];
	game->s = tmp[STH];
	game->e = tmp[EST];
	game->w = tmp[WST];
	ft_bzero(game->f, sizeof(int) * 3);
	ft_bzero(game->c, sizeof(int) * 3);
	if (!checkcolor(tmp, FLOOR, 0) || !checkcolor(tmp, CEIL, 0))
		return (ft_putstr_fd("Error in color\n", 1), freetmparr(tmp), \
		smart_ptr(NULL, FREE), exit(1));
	loadfc(game, tmp, FLOOR);
	loadfc(game, tmp, CEIL);
	i = -1;
	while (++i < 3)
		if (game->f[i] < 0 || game->f[i] > 255 || game->c[i] < 0 \
		|| game->c[i] > 255)
			return (ft_putstr_fd("Error in color\n", 1), freetmparr(tmp), \
			smart_ptr(NULL, FREE), exit(1));
}

static void	end(char *errmsg, char **paths, char **ss)
{
	ft_putstr_fd(errmsg, 1);
	freesplit(paths);
	freesplit(ss);
	exit(1);
}

// load the path for the 1st 6 files and map into game struct
void	loadvar(char *av[], t_game *game)
{
	char	**ss;
	int		i;
	char	*tmp[6];
	char	**paths;

	ft_bzero(tmp, sizeof(char *) * 6);
	ss = openfile(av[1]);
	if (!ss)
		return (ft_putstr_fd("Error FileProb\n", STDOUT_FILENO), exit(1));
	i = -1;
	while (++i < 6)
	{
		paths = ft_split(ss[i], ' ');
		if (!paths)
			return (ft_putstr_fd("Error Malloc\n", 1), freesplit(ss), exit(1));
		if (char2dlen(paths) != 2)
			return (end("Error BlankProb\n", paths, ss));
		tmp[identify(ss[i])] = ft_calloc(ft_strlen(paths[1]) + 2, sizeof(char));
		if (!tmp[identify(ss[i])])
			return (end("Error identity prob\n", paths, ss));
		ft_memcpy(tmp[identify(ss[i])], paths[1], ft_strlen(paths[1]));
		freesplit(paths);
	}
	return (loadcheckmap(game, ss, tmp), freesplit(ss), loadpath(game, tmp));
}
