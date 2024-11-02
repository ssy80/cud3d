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

char	**openfile(const char *dir)
{
	int		fd;
	char	*ans;
	t_list	*head;
	t_list	*cp;
	char	**arr;

	head = NULL;
	fd = open(dir, O_RDWR);
	ans = get_next_line(fd);
	if (!ans)
		return (closefile(fd), smart_ptr(NULL, END), NULL);
	while (ans)
	{
		cp = ft_lstnew(ans);
		if (!cp)
			return (ft_lstclear(&head, free), free(ans), closefile(fd), \
			smart_ptr(NULL, END), NULL);
		ft_lstadd_back(&head, cp);
		ans = get_next_line(fd);
	}
	arr = ll_to_2darr(head);
	if (!arr)
		return (ft_lstclear(&head, free), closefile(fd), NULL);
	return (closefile(fd), arr);
}
