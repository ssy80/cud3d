/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:14:32 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:14:35 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cp;

	cp = lst;
	while (cp != NULL)
	{
		if (cp->next == NULL)
			return (cp);
		cp = cp->next;
	}
	return (cp);
}
