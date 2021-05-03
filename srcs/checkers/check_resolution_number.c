/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_resolution_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:53:00 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:16:52 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_resolution_number(char *widthOrLength, t_settings *t_settings, int j)
{
	int	i;

	i = 0;
	while ((size_t)i < ft_strlen((const char *)widthOrLength))
	{
		if (ft_isdigit(widthOrLength[i]) == 0)
		{
			printf("Error\nBad resolution\n");
			return (1);
		}
		if (i >= 5)
		{
			if (j == 0)
				t_settings->sW = 500000;
			else
				t_settings->sH = 500000;
		}
		i++;
	}
	return (0);
}
