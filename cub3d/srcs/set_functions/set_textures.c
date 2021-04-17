/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:07:43 by rvena             #+#    #+#             */
/*   Updated: 2021/04/16 21:23:14 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void checkTexPath(char *res)
{
	int fd;
	int ret;
	char *temp;

	fd = open(res, O_RDONLY);
	ret = read(fd, temp, 0);
	if (ret == -1)
	{
		printf("Error\nBad texture path\n");
		close(fd);
		exit(-1);
	}
	close(fd);
}

static int setTexPath(const char *line, settings *settings, int d)
{
	char *tmp;
	int len;
	char *res;

	tmp = (char *)line;
	while(checkWhtSpc(*tmp) == 1)
		tmp++;
	len = ft_strlen(tmp);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if(res == NULL)
	{
		printf("Error\nMalloc setTexPath error\n");
		exit(-1);
	}
	ft_strlcpy(res, tmp, len + 1);
	checkTexPath(res);
	if(d == 1)
		settings->NO = res;
	else if(d == 2)
		settings->SO = res;
	else if(d == 3)
		settings->WE = res;
	else if(d == 4)
		settings->EA = res;
	else if(d == 5)
		settings->S = res;
	return(0);
}

int setTex(const char *line, settings *settings, int l)
{
	int i;
	
	i = 0;
	if(line[i] == 'N' && line[i + 1] == 'O' && checkWhtSpc(line[i + 2]) == 1)
		if(settings->NO == NULL)
			return(setTexPath(&line[i + 2], settings, 1));
		else
			return(printRepeatErr());
	else if(line[i] == 'S' && line[i + 1] == 'O' && checkWhtSpc(line[i + 2]) == 1)
		if(settings->SO == NULL)
			return(setTexPath(&line[i + 2], settings, 2));
		else
			return(printRepeatErr());
	else if(line[i] == 'W' && line[i + 1] == 'E' && checkWhtSpc(line[i + 2]) == 1)
		if(settings->WE == NULL)
			return(setTexPath(&line[i + 2], settings, 3));
		else
			return(printRepeatErr());
	else if(line[i] == 'E' && line[i + 1] == 'A' && checkWhtSpc(line[i + 2]) == 1)
		if(settings->EA == NULL)
			return(setTexPath(&line[i + 2], settings, 4));
		else
			return(printRepeatErr());
	else if(line[i] == 'S' && checkWhtSpc(line[i + 1]) == 1)
		{
			if(settings->S == NULL)
				return(setTexPath(&line[i + 2], settings, 5));
			else
				return(printRepeatErr());
		}
	printf("Error\nBad type argument\n");
	return(1);	
}