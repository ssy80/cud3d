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

int	identify(char *type)
{
	int	len;

	len = ft_strlen(type);
	if (len >= 1 && type[0] == 'F')
		return (FLOOR);
	if (len >= 1 && type[0] == 'C')
		return (CEIL);
	if (len >= 2)
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

void	loadfc(t_list *head, char *trim, t_game *game)
{
	int		idno;

	idno = identify(trim);
	if (idno == -1)
		return (ft_putstr_fd("Error\nParsing\n", 1), ft_lstclear(&head, free), \
		free(trim), exit(1));
	if (idno == FLOOR || idno == CEIL)
	{
		if (!checkcolorval(trim + 2))
			return (ft_putstr_fd("Error\nParsing\n", 1), \
			ft_lstclear(&head, free), free(trim), exit(1));
		if (idno == FLOOR)
			loadcolor(game->f, trim + 2, head);
		if (idno == CEIL)
			loadcolor(game->c, trim + 2, head);
	}
}

// parse and get path of nsew
void	loadnsew(t_list *head, char *trim, t_game *game)
{
	char	**str;
	int		idno;

	str = ft_split(trim, ' ');
	if (!str)
		return (ft_putstr_fd("Error\nMalloc\n", 1), ft_lstclear(&head, free), \
		exit(1), free(trim));
	if (char2dlen(str) != 2 && !(identify(str[0]) == FLOOR \
	|| identify(str[0]) == CEIL))
		return (ft_putstr_fd("Error\nParsing\n", 1), ft_lstclear(&head, free), \
		freesplit(str), free(trim), exit(1));
	idno = identify(str[0]);
	if (idno == -1 || ft_strlen(str[1]) >= 512)
		return (ft_putstr_fd("Error\nParsing\n", 1), ft_lstclear(&head, free), \
		freesplit(str), free(trim), exit(1));
	if (idno == NTH)
		ft_memcpy(game->n, str[1], ft_strlen(str[1]));
	if (idno == STH)
		ft_memcpy(game->s, str[1], ft_strlen(str[1]));
	if (idno == WST)
		ft_memcpy(game->w, str[1], ft_strlen(str[1]));
	if (idno == EST)
		ft_memcpy(game->e, str[1], ft_strlen(str[1]));
	freesplit(str);
}

// load content of file into game struct
// N,S,E,W, Floor, ceiling color
void	loadvar(t_list *head, t_game *game)
{
	t_list	*cp;
	int		n;
	char	*trim;

	cp = head;
	n = -1;
	ft_bzero(game, sizeof(t_game));
	while (cp && ++n < 6)
	{
		trim = ft_strtrim(cp->content, " \t\r\n");
		if (!trim)
			return (ft_putstr_fd("Error\nMalloc\n", 1), \
			ft_lstclear(&head, free), exit(1));
		loadnsew(head, trim, game);
		loadfc(head, trim, game);
		free(trim);
		cp = cp->next;
	}
	if (n != 6)
		return (ft_putstr_fd("Error\nIncomplete\n", 1), \
		ft_lstclear(&head, free), exit(1));
}
