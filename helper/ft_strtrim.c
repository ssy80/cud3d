/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:22:03 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:22:05 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

static char	*space(int i, int j, char const *s1)
{
	int		res;
	char	*ans;
	int		tmp;

	res = j - i + 1;
	tmp = -1;
	if (i > j)
		res = 0;
	ans = malloc(sizeof(char) * (res + 1));
	if (!ans)
		return (NULL);
	while (++tmp + i <= j)
		ans[tmp] = s1[i + tmp];
	ans[res] = '\0';
	return (ans);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	memo[256];
	int		i;
	int		j;

	i = -1;
	while (++i < 256)
		memo[i] = '0';
	j = ft_strlen(s1) - 1;
	i = -1;
	while (set[++i])
		memo[(int)set[i]] = '1';
	i = 0;
	while (i < j + 1 && s1[i] && memo[(int)s1[i]] == '1')
		i++;
	while (j > 0 && s1[j] && memo[(int)s1[j]] == '1')
		j--;
	return (space(i, j, s1));
}
