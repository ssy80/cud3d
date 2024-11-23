/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:13:09 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 16:13:16 by yoong            ###   ########.fr       */
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

int	identify(char *type)
{
	int	len;

	len = ft_strlen(type);
	if (len >= 2 && type[0] == 'F' && type[1] == ' ')
		return (FLOOR);
	if (len >= 2 && type[0] == 'C' && type[1] == ' ')
		return (CEIL);
	if (len >= 3 && type[2] == ' ')
	{
		if (type[0] == 'N' && type[1] == 'O')
			return (NTH);
		if (type[0] == 'S' && type[1] == 'O')
			return (STH);
		if (type[0] == 'W' && type[1] == 'E')
			return (WST);
		if (type[0] == 'E' && type[1] == 'A')
			return (EST);
	}
	return (-1);
}

bool	processline(char *s)
{
	char	**split;
	int		i;

	split = ft_split(s, ' ');
	if (!split)
		return (ft_putstr_fd("ft_split error", 1), exit(1), 0);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		return (ft_putstr_fd("Error: ", 1), ft_putstr_fd(s, 1), \
		freesplit(split), false);
	if (identify(split[0]) >= 0)
		return (freesplit(split), true);
	return (freesplit(split), false);
}

// check for 2 args
// check 2nd arg with len of 5 or more and ending with .cub
void	checking(int ac, char *av[], t_game *game)
{
	int			l;
	t_list		*content;
	bool		id[6];

	ft_bzero(id, sizeof(bool) * 6);
	if (ac != 2)
		return (ft_putstr_fd("only 1 arg\n", STDOUT_FILENO), exit(1));
	l = ft_strlen(av[1]);
	if (l < 5 || !(av[1][l - 4] == '.' && av[1][l - 3] == 'c' \
	&& av[1][l - 2] == 'u' && av[1][l - 1] == 'b'))
		return (ft_putstr_fd("incorrect file\n", STDOUT_FILENO), exit(1));
	content = openfile(av[1]);
	if (!content)
		return (ft_putstr_fd("Error\n", STDOUT_FILENO), exit(1));
<<<<<<< HEAD:err/err_manage.c
	loadvar(content, game);
	loadmap(content, game);
	ft_lstclear(&content, free);
}
=======
	l = -1;
	while (content[++l] && l < 6)
		if (identify(content[l]) != -1)
			id[identify(content[l])] = true;
	l = -1;
	while (++l < 6)
		if (!id[l])
			return (ft_putstr_fd("Error in identifier\n", 1), exit(1));
	freesplit(content);
}
<<<<<<< HEAD:err/err_manage.c
>>>>>>> 1e3b38f (loading n,s,e,w into game data):helper/err_manage.c
=======
>>>>>>> 8f7a0dd (some norm check and fixing color parsing):helper/err_manage.c
