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

static void	copymap(t_list *head, t_game *game, t_list *cp)
{
	int	i;

	i = -1;
	game->map = ft_calloc(game->row + 1, sizeof(char *));
	if (!game->map)
		return (ft_putstr_fd("Error\nMalloc\n", 1), \
		ft_lstclear(&head, free), exit(1));
	while (++i < game->row && cp)
	{
		game->map[i] = ft_calloc(game->col + 1, sizeof(char));
		if (!game->map[i])
			return (ft_putstr_fd("Error\nMalloc\n", 1), \
			ft_lstclear(&head, free), freesplit(game->map), exit(1));
		ft_memcpy(game->map[i], cp->content, ft_strlen(cp->content));
		cp = cp->next;
	}
}

// after loading map, free t_list from gnl
void	loadmap(t_list *head, t_game *game)
{
	int			l;
	t_list		*cp;
	t_list		*cp1;
	int			maxlen;
	char		*str;

	l = -1;
	cp = head;
	maxlen = 0;
	while (cp && ++l < 6)
		cp = cp->next;
	cp1 = cp;
	while (cp1)
	{
		str = cp1->content;
		if (str[ft_strlen(cp1->content) - 1] == '\n')
			str[ft_strlen(cp1->content) - 1] = '\0';
		maxlen = max(maxlen, ft_strlen(str));
		game->row++;
		cp1 = cp1->next;
	}
	game->col = maxlen;
	copymap(head, game, cp);
}
