/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:59:41 by rvena             #+#    #+#             */
/*   Updated: 2020/11/04 12:59:44 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *des, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned long	i;

	i = 0;
	dst = (unsigned char *)des;
	src = (unsigned char *)source;
	if ((des == NULL && source == NULL) || n == 0)
		return (des);
	if (des < source)
		while (i < n)
		{
			*(dst + i) = src[i];
			i++;
		}
	else
		while (n > 0)
		{
			*(dst + n - 1) = *(src + n - 1);
			n--;
		}
	return (des);
}
