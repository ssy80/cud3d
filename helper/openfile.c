/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:43:51 by yoong             #+#    #+#             */
/*   Updated: 2024/12/03 12:44:06 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

static void	closefile(int fd)
{
	close(fd);
	return ;
}

bool	isemptystr(char *s)
{
	int	set[128];
	int	i;

	i = -1;
	ft_bzero(set, sizeof(int) * 128);
	while (s[++i])
		set[(int) s[i]]++;
	i = -1;
	while (++i < 128)
	{
		if (i == ' ' || i == '\n' || i == '\t' || i == '\r')
			continue;
		if (set[i] > 0)
			return (false);
	}
	return (true);
}

t_list	*openfile(const char *dir)
{
	int		fd;
	char	*ans;
	t_list	*head;
	t_list	*cp;

	head = NULL;
	fd = open(dir, O_RDWR);
	ans = get_next_line(fd);
	while (ans)
	{
		if (!isemptystr(ans))
		{
			cp = ft_lstnew(ans);
			if (!cp)
				return (ft_lstclear(&head, free), free(ans), closefile(fd), \
				smart_ptr(NULL, END), NULL);
			ft_lstadd_back(&head, cp);
		}
		ans = get_next_line(fd);
	}
	return (closefile(fd), head);
}
