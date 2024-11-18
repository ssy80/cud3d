/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:13:09 by yoong             #+#    #+#             */
/*   Updated: 2024/11/01 16:13:16 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

void freesplit(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

char	**ll_to_2darr(t_list *head)
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
		return (NULL);
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

int	identify(char *type)
{
	int	len;

	len = ft_strlen(type);
	if (len >= 2 && type[0] == 'F' && type[1] == ' ')
		return (FLOOR);
	if (len >= 2 && type[0] == 'C' && type[1] == ' ')
		return (CEIL);
	if (len >= 3 && type[2] == ' '){
		if (type[0] == 'N' && type[1] == 'O')
			return (NTH);
		if (type[0] == 'S' && type[1] == 'O')
			return (STH);
		if (type[0] == 'W' && type[1] == 'E')
			return (WST);
		if (type[0] == 'E' && type[1] == 'A')
			return (EST);
	}
	return (-1);
}

bool	processline(char *s)
{
	char	**split;
	int		i;

	split = ft_split(s, ' ');
	if (!split)
		ft_putstr_fd("ft_split error", 1), exit(1);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		return (ft_putstr_fd("Error: ", 1), ft_putstr_fd(s, 1), freesplit(s), false);
	if (identify(s[0]) >= 0)
		return (freesplit(s), true);
	return (freesplit(s), false);
}

static void	closefile(int fd)
{
	close(fd);
	return ;
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
		return (closefile(fd), NULL);
	while (ans)
	{
		cp = ft_lstnew(ans);
		if (!cp)
			return (ft_lstclear(&head, free), free(ans), closefile(fd), NULL);
		ft_lstadd_back(&head, cp);
		ans = get_next_line(fd);
	}
	arr = ll_to_2darr(head);
	if (!arr)
		return (ft_lstclear(&head, free), closefile(fd), NULL);
	return (closefile(fd), arr);
}




// check for 2 args
// check 2nd arg with len of 5 or more and ending with .cub
void	checking(int ac, char *av[], t_game *game)
{
	int			l;
	t_list		*content;
	bool		id[6];

	ft_bzero(id, sizeof(bool) * 6);
	if (ac != 2)
		return (ft_putstr_fd("only 1 arg\n", STDOUT_FILENO), exit(1));
	l = ft_strlen(av[1]);
	if (l < 5 || !(av[1][l - 4] == '.' && av[1][l - 3] == 'c' \
	&& av[1][l - 2] == 'u' && av[1][l - 1] == 'b'))
		return (ft_putstr_fd("incorrect file\n", STDOUT_FILENO), exit(1));
	content = openfile(av[1]);
	if (!content)
		return (ft_putstr_fd("Error\n", STDOUT_FILENO), exit(1));
	loadvar(content, game);
	loadmap(content, game);
	ft_lstclear(&content, free);
}
