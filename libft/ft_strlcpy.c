/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:56:07 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:15:26 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char			*temp;
	unsigned long	i;

	temp = (char *)malloc((sizeof(char) * dstsize) + 1);
	temp[dstsize] = '\0';
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
	free(temp);
	return (ft_strlen(src));
}
