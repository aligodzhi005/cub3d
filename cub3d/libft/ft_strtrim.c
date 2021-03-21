/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:09:07 by rvena             #+#    #+#             */
/*   Updated: 2020/11/17 17:05:02 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const s1, char const *set)
{
	char	*temp_set;
	int		j;

	temp_set = (char *)set;
	j = 0;
	while (*temp_set != '\0')
	{
		if (*temp_set == s1)
		{
			j = 1;
			break ;
		}
		temp_set++;
	}
	return (j);
}

static void	set_i_j(char const *s1, char const *set, int *i, int *j)
{
	int		k;
	int		l;
	int		len;

	k = 0;
	l = ft_strlen(s1) - 1;
	len = l;
	while (ft_inset(s1[k], set) == 1)
		k++;
	while (ft_inset(s1[l], set) == 1)
		l--;
	*i = k;
	*j = len - l;
	if (*i == len + 1 && *j == len + 1)
		*j = 0;
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		len;
	int		t;

	if (s1 == NULL || set == NULL)
		return ((char*)(s1));
	len = ft_strlen(s1);
	i = 0;
	j = 0;
	set_i_j(s1, set, &i, &j);
	t = i;
	if (!(res = malloc((len + 1 - i - j) * sizeof(char))))
		return (NULL);
	t = ft_strlcpy(res, &s1[i], len - i - j + 1);
	return (res);
}
