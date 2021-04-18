/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:17:36 by rvena             #+#    #+#             */
/*   Updated: 2021/04/09 15:18:30 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int printBadArg(void)
{
	printf("Error\nBad Argument\n");
	return(1);
}

int printBadMap(void)
{
	printf("Error\nBad map\n");
	return(1);
}

int printRepeatErr(void)
{
	printf("Error\nRepeatable type indentifier\n");
	return(1);
}