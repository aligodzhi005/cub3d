/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:05:28 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:15:29 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	movement2(t_plr_data *plr, char **map)
{
	if (plr->mL == 1)
	{
		if (map[(int)((plr->posY - plr->planeY
					* 0.5))][(int)(plr->posX)] == '0')
			plr->posY -= plr->planeY * plr->moveSpeed * 0.1;
		if (map[(int)(plr->posY)][(int)((plr->posX
				- plr->planeX * 0.5))] == '0')
			plr->posX -= plr->planeX * plr->moveSpeed * 0.1;
	}
	else if (plr->mR == 1)
	{
		if (map[(int)((plr->posY
					+ plr->planeY * 0.5))][(int)(plr->posX)] == '0')
			plr->posY += plr->planeY * plr->moveSpeed * 0.1;
		if (map[(int)(plr->posY)][(int)((plr->posX
				+ plr->planeX * 0.5))] == '0')
			plr->posX += plr->planeX * plr->moveSpeed * 0.1;
	}
	if (plr->rR == 1)
		rotation(plr, 1);
	if (plr->rL == 1)
		rotation(plr, -1);
}

int	movement(t_plr_data *plr, char **map)
{
	if (plr->mF == 1)
	{
		if (map[(int)((plr->posY + plr->dirY * 0.5))][(int)(plr->posX)] == '0')
			plr->posY += plr->dirY * plr->moveSpeed * 0.1;
		if (map[(int)(plr->posY)][(int)((plr->posX + plr->dirX * 0.5))] == '0')
			plr->posX += plr->dirX * plr->moveSpeed * 0.1;
	}
	if (plr->mB == 1)
	{
		if (map[(int)((plr->posY - plr->dirY
					* plr->moveSpeed * 0.5))][(int)(plr->posX)] == '0')
			plr->posY -= plr->dirY * plr->moveSpeed * 0.1;
		if (map[(int)(plr->posY)][(int)((plr->posX
				- plr->dirX * plr->moveSpeed * 0.5))] == '0')
			plr->posX -= plr->dirX * plr->moveSpeed * 0.1;
	}
	movement2(plr, map);
	return (0);
}
