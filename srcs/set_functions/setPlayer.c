/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setPlayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:56:59 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:32:39 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	setPlayer(t_all_data *everything, int i, int j)
{
	if (everything->player->posX == 0)
	{
		everything->player->posX = j + 0.5;
		everything->player->posY = i + 0.5;
		setDirPlane(everything->map[i][j], everything->player);
		everything->map[i][j] = '0';
	}
	else
	{
		printf("Error\nToo many players\n");
		exit(-1);
	}
}
