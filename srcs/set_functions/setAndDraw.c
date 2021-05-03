/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setAndDraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:34:13 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:17:18 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	setAndDraw(t_all_data *ever, t_sprite_data *listOfSpr, int i,
			t_settings *set)
{
	t_tex_data	*spr;
	double		transformY;

	spr = ever->sprite1;
	transformY = setParForSpr(ever, listOfSpr, i, spr);
	drawSprite(ever, spr, set, transformY);
}
