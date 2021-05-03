/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:59:41 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:21:37 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check(unsigned char	*dst, unsigned char	*src, int n)
{
	while (n > 0)
	{
		*(dst + n - 1) = *(src + n - 1);
		n--;
	}
}

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
	{
		while (i < n)
		{
			*(dst + i) = src[i];
			i++;
		}
	}
	else
	{
		check(dst, src, n);
	}
	return (des);
}
