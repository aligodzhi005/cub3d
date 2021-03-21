/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:37:12 by rvena             #+#    #+#             */
/*   Updated: 2020/10/29 16:37:15 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *des, const void *source, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned long	i;

	i = 0;
	dst = (unsigned char *)des;
	src = (unsigned char *)source;
	if ((dst == NULL && src == NULL) || n == 0)
		return (NULL);
	while (i < n)
	{
		*(dst + i) = *(src + i);
		if (*(dst + i) == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
