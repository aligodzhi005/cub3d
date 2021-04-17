/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_res_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:51:41 by rvena             #+#    #+#             */
/*   Updated: 2021/04/09 14:51:58 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int checkResNumber(char **res, int number, int length)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(res[i][j])
		j++;
	if(j != length)
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	while(res[i])
		i++;
	if(i != number)
	{
		printf("Error\nBad number of arguments\n");
		return(1);
	}
	return(0);
}