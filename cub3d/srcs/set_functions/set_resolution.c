/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:59:59 by rvena             #+#    #+#             */
/*   Updated: 2021/04/12 16:12:33 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int line_correction(const char *line)
{
	size_t i;
	int isSpace;
	char *tmp;

	i = 0;
	tmp = (char *)line;
	if(!line)
		return(0);
	while(tmp[i] != '\0')
	{
		// if(ft_isprint(tmp[i]) == 0 || tmp[i] == '"')
		if(checkWhtSpc(tmp[i]) == 1)
			tmp[i] = ' ';
		i++;
	}
	return(i);
}

static char	**ft_free_res(char **res)
{
	int k;

	k = 0;
	while (res[k] != NULL)
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

int set_resolution(const char *line, settings *settings)
{
	char **res;
	
	line_correction(line);
	if(settings->sW != 0 && settings->sH != 0)
		return(printRepeatErr());
	res = ft_split(line, ' ');
	if(res[0][1] != '\0' || res[0][0] != 'R')
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	if(check_resolution_number(res[1]) == 1 || 
		checkResNumber(res, 3, 1) == 1)
		return(1);
	if(check_resolution_number(res[2]) == 1)
		return(1);
	settings->sW = ft_atoi(res[1]);
	settings->sH = ft_atoi(res[2]);
	ft_free_res(res);
	return(0);
}