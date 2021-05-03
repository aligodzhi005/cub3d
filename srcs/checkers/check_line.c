/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:39:23 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:19:39 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	checkt_settings(t_settings *t_settings, const char *line)
{
	int	i;

	i = 0;
	if (t_settings->sW != 0 && t_settings->sH != 0)
		if (t_settings->floor != -1 && t_settings->ceilling != -1)
			if (t_settings->NO != NULL && t_settings->SO != NULL)
				if (t_settings->WE != NULL)
					if (t_settings->EA != NULL && t_settings->S != NULL)
						while (line[i] != '\0')
							if (ft_isprint(line[i++]))
								return (1);
	if (lineEmptyOrNot((char *)line) == 1)
		return (1);
	return (0);
}

static int	check_line2(const char *line, t_settings *t_settings, int i)
{
	if (line[i] == 'R')
	{
		if (set_resolution(line, t_settings) == 1)
			return (1);
		else
			return (2);
	}
	else if (ft_strchr("FC", line[i]) != NULL)
	{
		if (chooseFlOrCl(&line[i], t_settings) != 0)
			return (1);
		else
			return (2);
	}
	else if (ft_strchr("NSWE", line[i]) != NULL)
	{
		if (setTex(&line[i], t_settings) == 0)
			return (2);
		else
			return (1);
	}
	return (0);
}

int	check_line(const char *line, t_settings *t_settings)
{
	size_t	line_length;
	int		i;
	int		res;

	i = 0;
	line_length = checkt_settings(t_settings, line);
	if (line_length == 1)
		return (0);
	while (line[i])
	{
		if (ft_strchr("RNSWEFC", line[i]) == NULL)
			if (checkWhtSpc(*line) == 0)
				return (printBadArg());
		res = check_line2(line, t_settings, i);
		if (res > 0)
			return (res);
		i++;
	}
	return (printBadArg());
}
