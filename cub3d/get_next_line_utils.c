/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:54:55 by rvena             #+#    #+#             */
/*   Updated: 2021/03/20 19:11:55 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (NULL);
}

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char			temp[dstsize];
	unsigned long	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize != 0)
	{
		dstsize--;
		while (i < dstsize && src[i] != '\0')
		{
			temp[i] = src[i];
			dst[i] = temp[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

unsigned long	ft_strlen(const char *src)
{
	unsigned char	*temp_src;
	unsigned long	count;

	count = 0;
	temp_src = (unsigned char *)src;
	while (*temp_src != '\0')
	{
		count++;
		temp_src++;
	}
	return (count);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}	
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		res[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char			*ft_strdup(const char *s1)
{
	char *temp_s1;

	temp_s1 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (temp_s1 == NULL)
		return (NULL);
	ft_strlcpy(temp_s1, s1, ft_strlen(s1) + 1);
	return (temp_s1);
}
