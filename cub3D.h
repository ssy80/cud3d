/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:30:43 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 14:30:45 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

# define END 0
# define FREE -1
# define ADD 1

// ft linkedlist
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// ft memory
void	ft_bzero(void *b, size_t len);
void	*ft_calloc(size_t number, size_t size);
// ft str
int		ft_isalnum(int a);
int		ft_isalpha(int a);
int		ft_isdigit(int a);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
// gnl
char	*get_next_line(int fd);
// clean up
void	smart_ptr(void *ptr, int action);
// error checking
void	checking(int ac, char *av[]);
#endif