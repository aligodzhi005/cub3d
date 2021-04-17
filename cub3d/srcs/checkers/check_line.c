/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:39:23 by rvena             #+#    #+#             */
/*   Updated: 2021/04/09 15:09:41 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int checkSettings(settings *settings, const char *line)
{
	int i;

	i = 0;
	if(settings->sW != 0 && settings->sH != 0
		&& settings->floor != -1 && settings->ceilling != -1)	
		if(settings->NO != NULL && settings->SO != NULL	&& 
			settings->WE != NULL && settings->EA != NULL
			&& settings->S != NULL)
			{
				// if(line[i] == '\0')
				// 	return(1);
				while(line[i] != '\0')
				{
					if(ft_isprint(line[i++]))
						return (1);
					// i++;
				}
			}
	if(lineEmptyOrNot((char *)line) == 1)
		return(1);
	return(0);
}

int	check_line(const char *line, settings *settings)
{
	size_t line_length;
	int i;

	i = 0;
	line_length = checkSettings(settings, line);
	if(line_length == 1)
		return(0);
	// else if(line_length == 2)
	// 	return(2);
	// line_length = line_correction(line);
	// if(line_length > settings->mapW)
	// 	settings->mapW = line_length;
	while(line[i])
	{
		if(ft_strchr("RNSWEFC", line[i]) == NULL)
			if(checkWhtSpc(*line) == 0)
			{
				printf("Error\nBad argument\n");
				return(1);	
			}
		if(line[i] == 'R')
		// if(ft_strnstr(line, "R", line_length))
		{
			if (set_resolution(line, settings) == 1)
				return(1);
			else
				return(2);
		}
		else if(ft_strchr("FC", line[i]) != NULL)
		// else if(ft_strnstr(line, "S ", line_length))
		{
			if(chooseFlOrCl(&line[i], settings) != 0)
				return(1);
			else
				return(2);
		}
		else if(ft_strchr("NSWE", line[i]) != NULL)
		// else if(ft_strchr("NSWE", line[i]) != NULL && ft_strchr("OAE", line[i + 1]) != NULL)
		{
			if(setTex(&line[i], settings, 2) == 0)
				return(2);
			else
				return(1);
		}
		i++;
	}
	printf("Error\nBad argument\n");
	return(1);
}