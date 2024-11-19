/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_openfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:19:17 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 18:19:26 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	closefile(int fd)
{
	close(fd);
	return ;
}

static char	**ll_to_2darr(t_list *head)
{
	char	**arr;
	int		i;
	int		size;
	t_list	*np;

	i = -1;
	np = head;
	size = ft_lstsize(head);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (smart_ptr(NULL, END), NULL);
	smart_ptr(arr, ADD);
	arr[size] = 0;
	while (head)
	{
		arr[++i] = head->content;
		np = head->next;
		free(head);
		head = NULL;
		head = np;
	}
	return (arr);
}

bool	isemptystr(char *s)
{
	char *res;

	if (!s)
		return (true);
	res = ft_strtrim(s, " \n\t\r");
	if (ft_strlen(res) == 0)
	{
		free(s);
		s = NULL;
		return (free(res), true);
	}
	return (free(res), false);
}

char	**openfile(const char *dir)
{
	int		fd;
	char	*ans;
	t_list	*head;
	t_list	*cp;
	char	**arr;

	head = NULL;
	fd = open(dir, O_RDWR);
	while ((ans = get_next_line(fd)))
	{
		if (isemptystr(ans))
			continue;
		cp = ft_lstnew(ans);
		if (!cp)
			return (ft_lstclear(&head, free), free(ans), closefile(fd), \
			smart_ptr(NULL, END), NULL);
		ft_lstadd_back(&head, cp);
	}
	arr = ll_to_2darr(head);
	if (!arr)
		return (ft_lstclear(&head, free), closefile(fd), NULL);
	return (closefile(fd), arr);
}
