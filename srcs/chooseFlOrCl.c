/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooseFlOrCl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:21:24 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:33:28 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	chooseFlOrCl(const char *line, t_settings *t_settings)
{
	int	i;

	i = 0;
	if (line[i] == 'F' && checkWhtSpc(line[i + 1]) == 1)
		return (setColor(&line[i + 1], &t_settings->floor));
	else if (line[i] == 'C' && checkWhtSpc(line[i + 1]) == 1)
		return (setColor(&line[i + 1], &t_settings->ceilling));
	else
		return (printBadArg());
}
