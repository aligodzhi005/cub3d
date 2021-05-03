/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:50:23 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:03:24 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_of_word(char const *s, char c)
{
	int	count;
	int	was;
	int	i;

	i = 0;
	was = 0;
	count = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && was == 1)
			was = 0;
		if (s[i] != c && was == 0)
		{
			count++;
			was = 1;
		}
		i++;
	}
	return (count);
}

static char	*ft_make_word(char const *s, int i, int j)
{
	char	*word;
	int		t;

	word = malloc(sizeof(char) * (i - j + 1));
	if (word == NULL)
		return (NULL);
	t = ft_strlcpy(word, &s[j], i - j + 1);
	return (word);
}

static char	**ft_free_res(char **res)
{
	int	k;

	k = 0;
	while (res[k] != NULL)
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

static void	skip(char const *s, int *i, int *j, char c)
{
	while (s[*i] == c)
		*i += 1;
	*j = *i;
	while (s[*i] != c && s[*i] != '\0')
		*i += 1;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_of_word(s, c) + 1));
	if (!(res))
		return (NULL);
	while (s[i] != '\0')
	{
		skip(s, &i, &j, c);
		if (i > j)
		{
			res[k] = ft_make_word(s, i, j);
			if (!(res[k++]))
				return (ft_free_res(res));
		}
	}
	res[k] = NULL;
	return (res);
}
