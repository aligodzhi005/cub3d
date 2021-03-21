/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:56:07 by rvena             #+#    #+#             */
/*   Updated: 2020/10/30 11:56:09 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
