/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:39:23 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 20:27:41 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	checkSettings(settings *settings, const char *line)
{
	int	i;

	i = 0;
	if (settings->sW != 0 && settings->sH != 0)
	{
		if (settings->floor != -1 && settings->ceilling != -1)
			if (settings->NO != NULL && settings->SO != NULL)
				if (settings->WE != NULL)
					if (settings->EA != NULL && settings->S != NULL)
						while (line[i] != '\0')
							if (ft_isprint(line[i++]))
								return (1);
	}
	if (lineEmptyOrNot((char *)line) == 1)
		return (1);
	return (0);
}

static int	check_line2(const char *line, settings *settings, int i)
{
	if (line[i] == 'R')
	{
		if (set_resolution(line, settings) == 1)
			return (1);
		else
			return (2);
	}
	else if (ft_strchr("FC", line[i]) != NULL)
	{
		if (chooseFlOrCl(&line[i], settings) != 0)
			return (1);
		else
			return (2);
	}
	else if (ft_strchr("NSWE", line[i]) != NULL)
	{
		if (setTex(&line[i], settings, 2) == 0)
			return (2);
		else
			return (1);
	}
	return (0);
}

int	check_line(const char *line, settings *settings)
{
	size_t	line_length;
	int		i;
	int		res;

	i = 0;
	line_length = checkSettings(settings, line);
	if (line_length == 1)
		return (0);
	while (line[i])
	{
		if (ft_strchr("RNSWEFC", line[i]) == NULL)
			if (checkWhtSpc(*line) == 0)
				return (printBadArg());
		res = check_line2(line, settings, i);
		if (res > 0)
			return (res);
		i++;
	}
	return (printBadArg());
}
