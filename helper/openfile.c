/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:43:51 by yoong             #+#    #+#             */
/*   Updated: 2024/12/24 11:44:06 by ssian            ###   ########.fr       */
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
			continue ;
		if (set[i] > 0)
			return (false);
	}
	return (true);
}

static void	endgnl(int fd)
{
	char	*ans;

	ans = get_next_line(fd);
	while (ans)
	{
		free(ans);
		ans = get_next_line(fd);
	}
	ans = NULL;
}

void	checknfree(t_list **head, char **ans, int fd)
{
	t_list	*cp;
	int		i;

	free(*ans);
	*ans = NULL;
	i = 0;
	if (!head)
		return (free(ans));
	cp = *head;
	while (cp && ++i >= 0)
		cp = cp->next;
	if (i >= 7)
		return (ft_lstclear(head, free), closefile(fd), \
		free(get_next_line(fd)), endgnl(fd), \
		ft_putstr_fd("Error\nParsing\n", 1), exit(1));
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
				return (ft_lstclear(&head, free), free(ans), \
				closefile(fd), NULL);
			ft_lstadd_back(&head, cp);
		}
		else
			checknfree(&head, &ans, fd);
		ans = get_next_line(fd);
	}
	return (closefile(fd), head);
}
