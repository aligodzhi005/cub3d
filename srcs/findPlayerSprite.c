/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findPlayerSprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:55:38 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:33:28 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	malSprOrdDistAndCheckPlayer(t_all_data *everything)
{
	everything->spriteOrder = (int *)malloc(sizeof(int)
			* everything->numOfSprite);
	if (everything->spriteOrder == NULL)
	{
		printf("Error\nMalloc spriteOrder failed\n");
		exit(-1);
	}
	everything->spriteDist = (double *)malloc(sizeof(double)
			* everything->numOfSprite);
	if (everything->spriteDist == NULL)
	{
		printf("Error\nMalloc spriteDist failed\n");
		exit(-1);
	}
}

int	findPlayerSprite(t_all_data *everything)
{
	int	i;
	int	j;

	i = 0;
	while (i < everything->t_settings->mapH)
	{
		j = 0;
		while (j < everything->t_settings->mapW)
		{
			if (ft_strchr("NSWE", everything->map[i][j]))
				setPlayer(everything, i, j);
			else if (everything->map[i][j] == '2')
				setListOfSprite(everything, i, j);
			j++;
		}
		i++;
	}
	if (everything->player->posX == 0)
	{
		printf("Error\nNo player\n");
		exit(-1);
	}
	malSprOrdDistAndCheckPlayer(everything);
	return (0);
}
