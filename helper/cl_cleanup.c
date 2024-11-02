/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:45:09 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 14:45:23 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// prevent double free
// free only smartptr without freeing content
void	voidfunc(void *ptr)
{
	(void) ptr;
	return ;
}

/* smart pointer for holding malloc ptr
if ptr is null, action can be any int
use END when malloc failure
use ADD to add malloc ptr
use FREE when program ends smoothly */
void	smart_ptr(void *ptr, int action)
{
	static t_list	*head = NULL;
	t_list			*tmp;

	if (action == END)
		return (ft_lstclear(&head, free), \
		ft_putstr_fd("malloc failure", STDOUT_FILENO), exit(1));
	if (action == FREE)
		return (ft_lstclear(&head, voidfunc));
	if (!ptr)
		return ;
	if (action == ADD)
	{
		tmp = ft_lstnew(ptr);
		if (!tmp)
			return (ft_lstclear(&head, free));
		return (ft_lstadd_back(&head, tmp));
	}
}
