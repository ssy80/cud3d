/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:14:48 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:14:51 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cp;
	t_list	*head;
	t_list	*t;
	void	*c;

	cp = lst;
	if (!cp || !f || !del)
		return (NULL);
	c = f(cp->content);
	head = ft_lstnew(c);
	if (head == NULL)
		return (free(c), NULL);
	t = head;
	cp = cp->next;
	while (cp != NULL)
	{
		c = f(cp->content);
		t->next = ft_lstnew(c);
		t = t->next;
		if (!t)
			return (free(c), ft_lstclear(&head, del), NULL);
		cp = cp->next;
	}
	t->next = NULL;
	return (head);
}
