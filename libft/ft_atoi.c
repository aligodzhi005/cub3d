/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:41:49 by rvena             #+#    #+#             */
/*   Updated: 2021/04/26 21:18:14 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = -1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (res == -1)
				res = 0;
			res = (res * 10 + *str - 48);
		}
		else
			break ;
		str++;
	}
	return (res);
}
