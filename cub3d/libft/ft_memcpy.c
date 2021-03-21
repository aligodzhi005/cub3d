/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:30:19 by rvena             #+#    #+#             */
/*   Updated: 2020/10/29 15:30:21 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned long	i;

	i = 0;
	dst = (unsigned char *)des;
	src = (unsigned char *)source;
	if ((dst == NULL && src == NULL) || n == 0)
		return (des);
	while (i < n)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	return (des);
}
