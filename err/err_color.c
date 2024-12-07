/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:56:58 by yoong             #+#    #+#             */
/*   Updated: 2024/12/04 19:57:02 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include "../header/libft.h"

static bool	parsenum(char *s, int *color)
{
	char	**split;
	int		tmp;

	split = ft_split(s, ' ');
	if (!split)
		return (false);
	if (char2dlen(split) != 1)
		return (freesplit(split), false);
	tmp = ft_atoi(split[0]);
	if (tmp > 255 || tmp < 0)
		return (freesplit(split), false);
	*color = tmp;
	return (freesplit(split), true);
}

void	loadcolor(int *arr, char *s, t_list *head)
{
	char	*trim;
	char	**split;
	int		i;

	trim = ft_strtrim(s, " \n\t\r");
	if (!trim)
		return (ft_putstr_fd("Error Malloc\n", 1), ft_lstclear(&head, free), \
		exit(1));
	split = ft_split(trim, ',');
	if (!split)
		return (ft_putstr_fd("Error Malloc\n", 1), ft_lstclear(&head, free), \
		free(trim), exit(1));
	if (char2dlen(split) != 3)
		return (ft_putstr_fd("Error color\n", 1), ft_lstclear(&head, free), \
		free(trim), freesplit(split), exit(1));
	i = -1;
	while (++i < 3)
	{
		if (!parsenum(split[i], arr + i))
			return (ft_putstr_fd("Error color\n", 1), ft_lstclear(&head, free), \
			free(trim), freesplit(split), exit(1));
	}
	return (free(trim), freesplit(split));
}

// ensure that there are 2 commma
// ensure that there are only ' ', ',' and number
// len must be more than 5 
// max num of digit is 9 
bool	checkcolorval(char *str)
{
	int	len;
	int	comma;
	int	i;
	int	digit;

	len = ft_strlen(str);
	i = -1;
	comma = 0;
	digit = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' ')
			return (false);
		if (str[i] == ',')
			comma++;
		if (ft_isdigit(str[i]))
			digit++;
	}
	if (comma != 2 || len < 5 || !ft_isdigit(str[len - 1]) || digit > 9)
		return (false);
	return (true);
}
