/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:42:35 by yoong             #+#    #+#             */
/*   Updated: 2024/05/25 17:42:39 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listc	*ft_lstnewgnl(char c)
{
	t_listc	*ans;

	ans = ft_calloc(1, sizeof(t_listc));
	if (!ans)
		return (NULL);
	ans->c = c;
	ans->next = NULL;
	return (ans);
}

void	ft_lstdelonegnl(t_listc *lst)
{
	free(lst);
	lst = NULL;
}

char	*str_created(int i)
{
	char	*ans;

	ans = ft_calloc(i + 1, sizeof(char));
	if (!ans)
		return (NULL);
	ans[i] = '\0';
	return (ans);
}

void	free_linked_list(t_listc **head)
{
	t_listc	*cp;
	t_listc	*np;

	cp = *head;
	while (cp)
	{
		np = cp->next;
		ft_lstdelonegnl(cp);
		cp = np;
	}
	*head = NULL;
}
