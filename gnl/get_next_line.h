/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:45:23 by yoong             #+#    #+#             */
/*   Updated: 2024/05/25 17:45:27 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../header/cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_listc
{
	char			c;
	struct s_listc	*next;
}	t_listc;

char	*get_next_line(int fd);
t_listc	*ft_lstnewgnl(char c);
void	ft_lstdelonegnl(t_listc *lst);
char	*str_created(int i);
void	free_linked_list(t_listc **head);

#endif