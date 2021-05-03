/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countComa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:29:49 by rvena             #+#    #+#             */
/*   Updated: 2021/04/26 21:17:05 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	countComma(char *tmp)
{
	int	i;
	int	countC;

	i = 0;
	countC = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == ',')
			countC++;
		i++;
	}
	if (countC != 2)
	{
		printf("Error\nWrong number of comma\n");
		exit(-1);
	}
}
