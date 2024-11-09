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
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "minilibx-linux/mlx.h"

# define END 0
# define FREE -1
# define ADD 1
# define PI 3.14159265359
# define WIDTH 600
# define HEIGHT 300
# define BLOCK 64
# define DEBUG 0

typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}	t_list;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	rleft;
	bool	rright;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_player;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_player		player;
	char			**map;
}	t_game;

// ft linkedlist
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// ft memory
void		ft_bzero(void *b, size_t len);
void		*ft_calloc(size_t number, size_t size);
// ft str
int			ft_isalnum(int a);
int			ft_isalpha(int a);
int			ft_isdigit(int a);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
// gnl
char		*get_next_line(int fd);
// clean up
void		smart_ptr(void *ptr, int action);
// error checking
void		checking(int ac, char *av[]);
// player
void		move_player(t_player *player);
int			key_down(int keycode, t_player *player);
int			key_up(int keycode, t_player *player);
void		init_player(t_player *player);
// map
char		**get_map(void);
#endif