/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_deepcopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:08:56 by yoong             #+#    #+#             */
/*   Updated: 2024/11/09 01:09:03 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	initarr(void *arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((unsigned char *)arr)[i++] = 0;
}

char	**deepcopy(char **map, int lc, int lr)
{
	char	**copy;
	int		i;
	int		j;

	i = -1;
	copy = malloc((lc + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[lc] = 0;
	while (++i < lc)
	{
		j = -1;
		copy[i] = malloc((lr + 1) * sizeof(char));
		// if (!copy[i])
		// 	return (freearray(copy, i), NULL);
		while (++j < lr)
			copy[i][j] = map[i][j];
		copy[i][j] = '\0';
	}
	return (copy);
}
