/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setAndDraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:34:13 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 19:39:21 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	setAndDraw(all_data *ever, sprite_data *listOfSpr, int i, settings *set)
{
	player_data	*pl;
	tex_data	*spr;
	double		transformY;

	spr = ever->sprite1;
	transformY = setParForSpr(ever, listOfSpr, i, spr);
	drawSprite(ever, spr, set, transformY);
}
