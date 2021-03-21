/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:33:44 by rvena             #+#    #+#             */
/*   Updated: 2020/10/31 18:33:45 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *temp_s1;

	temp_s1 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (temp_s1 == NULL)
		return (NULL);
	ft_strlcpy(temp_s1, s1, ft_strlen(s1) + 1);
	return (temp_s1);
}
