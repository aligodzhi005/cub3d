/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:54:11 by rvena             #+#    #+#             */
/*   Updated: 2020/10/30 12:54:13 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (dstsize > j)
	{
		while (src[i] != '\0' && (j + i) < dstsize - 1)
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
	}
	else
		j = dstsize;
	return (ft_strlen(src) + j);
}
