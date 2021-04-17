/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalFunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:23:29 by rvena             #+#    #+#             */
/*   Updated: 2021/04/09 14:31:46 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		checkWhtSpc(char chr)
{
	if(chr != ' ' && chr != '\t' && chr != '\n' && chr != '\v' && 
		chr != '\f' && chr != '\r')
		return(0);
	return (1);
}

int		lineEmptyOrNot(char *line)
{
	int i = 0;
	while (line[i] != '\0')
	{
		if(checkWhtSpc(line[i]) == 0)
			return(0);
		i++;
	}
	return(1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}