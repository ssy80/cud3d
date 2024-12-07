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
	loadvar(content, game);
	loadmap(content, game);
	ft_lstclear(&content, free);
}
