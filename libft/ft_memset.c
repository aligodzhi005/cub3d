/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:00:48 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:09:56 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*dst;

	dst = str;
	i = 0;
	while (i < n)
	{
		*dst = (unsigned char)c;
		dst++;
		i++;
	}
	return (str);
}
