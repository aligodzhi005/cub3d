/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_resolution_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:53:00 by rvena             #+#    #+#             */
/*   Updated: 2021/04/09 14:53:34 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int check_resolution_number(char *widthOrLength)
{
	int i;
	i = 0;
	while (i < ft_strlen((const char *)widthOrLength))
	{
		if(ft_isdigit(widthOrLength[i]) == 0 || i >= 5)
		{
			printf("Error:\nBad resolution\n");
			return(1);
		}
		i++;
	}
	return(0);
}