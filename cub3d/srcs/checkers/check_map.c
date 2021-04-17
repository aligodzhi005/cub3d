/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:41:13 by rvena             #+#    #+#             */
/*   Updated: 2021/04/16 20:42:44 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int mapNormalize(char **map, settings *settings)
{
	char *tmp;
	// char *spc;
	size_t line_length;
	int i;

	// line_length = 0;
	i = 0;
	while(i < settings->mapH)
	{
		line_length = ft_strlen(map[i]);
		if(line_length <= settings->mapW)
		{
			tmp = map[i];
			map[i] = (char *)malloc((settings->mapW + 1) * sizeof(char));
			if(map[i] == NULL)
			{
				printf("Error\nMalloc map[i] error");
				exit(-1);
			}
			map[i][settings->mapW + 1] = '\0';
			map[i] = ft_memcpy(map[i], tmp, line_length);
			while(line_length < settings->mapW + 1)
			// {
				map[i][line_length++] = ' ';
				// line_length++;
			// }
			free(tmp);
		}
		i++;
	}
	return(0);
}

int checkMap(char **map, settings *settings)
{
	int i;
	int j; 
	int start;

	start = 0;
	i = 0;
	// моя задумка в том, чтобы проверять есть ли символ в списке разрешенных - это во-первых
	// должен подниматься флаг startHor, если наткнулись на 1 - это во-вторых
	// если символ является 0,N,S,W,E,2, то должен быть поднят флаг startHor и после него не должно быть ' ' или '\0' - это в-третьих
	// такая же проверка для вертикальной линии
	// check horizontal line


	while(i < settings->mapH)
	{
		start = 0;
		j = 0;
		while(map[i][j] != '\0')
		{
			// printf("i = %d j = %d\n", i, j);
			if(ft_strchr("012NSWE ", map[i][j]) == NULL)
			{
				printf("Ku\n");
				return(printBadMap());
			}
			else if(map[i][j] == '1')
				start = 1;
			else if(ft_strchr("02NSWE", map[i][j]) != NULL)
				if(start != 1 || map[i][j + 1] == ' ' || map[i][j + 1] == '\0' || map[i][j - 1] == ' ')
				{
					printf("tut\n");
					return(printBadMap());
				}
			j++;
		}
		if(j > settings->mapW)
			settings->mapW = j;
		i++;
	}
	printf("mapW = %d\n", settings->mapW);
	mapNormalize(map, settings);
	j = 0;
	while(j < settings->mapW)
	{
		start = 0;
		i = 0;
		while(i < settings->mapH)
		{
			if(map[i][j] == '1')
				start = 1;
			else if(ft_strchr("02NSWE", map[i][j]) != NULL)
				if(start != 1 || map[i + 1][j] == ' ' || map[i + 1][j] == '\0' || map[i - 1][j] == ' ')
					return(printBadMap());
			i++;
		}
		j++;
	}
	return(0);
}