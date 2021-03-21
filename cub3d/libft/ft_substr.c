/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:20:48 by rvena             #+#    #+#             */
/*   Updated: 2020/11/01 15:20:50 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*substr;

	if (!s)
		return (NULL);
	i = 0;
	if (start > (unsigned int)ft_strlen(s))
		len = 0;
	if (!(substr = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	while (len > 0 && s[i] != '\0')
	{
		*(substr + i) = *(s + start + i);
		i++;
		len--;
	}
	*(substr + i) = '\0';
	return (substr);
}
