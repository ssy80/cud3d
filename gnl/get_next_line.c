/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:40:58 by yoong             #+#    #+#             */
/*   Updated: 2024/05/25 17:41:00 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	search(t_listc *head)
{
	t_listc	*cp;

	cp = head;
	while (cp)
	{
		if (cp->c == '\n')
			return (1);
		cp = cp->next;
	}
	return (0);
}

void	append_str(t_listc **head, char *buf, int len)
{
	t_listc	*cp;
	t_listc	*pp;
	int		i;

	i = 0;
	pp = *head;
	while (pp && pp->next)
		pp = pp->next;
	while (buf[i] && i < len)
	{
		cp = ft_lstnewgnl(buf[i]);
		if (*head == NULL)
		{
			*head = cp;
			pp = cp;
		}
		else
		{
			pp->next = cp;
			pp = cp;
		}
		i++;
	}
}

void	copydel(char *ans, t_listc **head, int len)
{
	int		j;
	t_listc	*cp;
	t_listc	*np;

	j = 0;
	cp = *head;
	while (j < len && cp)
	{
		ans[j] = cp->c;
		np = cp->next;
		ft_lstdelonegnl(cp);
		cp = np;
		j++;
	}
	*head = cp;
}

static char	*get_line(t_listc **head)
{
	char	*ans;
	t_listc	*cp;
	int		i;
	int		len;

	cp = *head;
	i = 0;
	while (cp && cp->c != '\n' && ++i >= 0)
		cp = cp->next;
	len = i;
	if (cp && cp->c == '\n')
		len = i + 1;
	ans = str_created(len);
	copydel(ans, head, len);
	if (ans[0] == '\0')
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}

char	*get_next_line(int fd)
{
	char			*buf;
	int				fdread;
	static t_listc	*head = NULL;
	char			*ans;

	fdread = 1;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (free_linked_list(&head), NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (fdread > 0 && !search(head))
	{
		fdread = read(fd, buf, BUFFER_SIZE);
		if (fdread == -1)
			return (free_linked_list(&head), free(buf), NULL);
		if (fdread > 0)
			append_str(&head, buf, fdread);
	}
	free(buf);
	ans = get_line(&head);
	return (ans);
}
