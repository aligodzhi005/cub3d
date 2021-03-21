/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:04:42 by rvena             #+#    #+#             */
/*   Updated: 2020/11/04 14:04:44 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *temp_s;

	temp_s = (unsigned char*)s;
	while (n > 0)
	{
		if (*temp_s == (unsigned char)c)
			return (temp_s);
		temp_s++;
		n--;
	}
	return (0);
}
