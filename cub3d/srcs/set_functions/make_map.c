/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:47:09 by rvena             #+#    #+#             */
/*   Updated: 2021/04/17 18:04:29 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char **mallocMap(int size)
{
	char **map;

	map = (char **)malloc(sizeof(char *) * (size));
	if(map == NULL)
	{
		printf("Error\nMalloc map error\n");
		exit(-1);
	}
	map[0] = "\0";
	return(map);
}

static t_list *skipEmptyLine(t_list *head, int *i)
{
	char *vis;
	t_list *tmp;

	*i = 0;
	tmp = head;
	while(tmp != NULL)
	{
		vis = tmp->content;
		if(lineEmptyOrNot(vis) == 1)
		{
			*i += 1;
			tmp = tmp->next;
		}
		else
			return(tmp);
	}
	return(tmp);
}

char **makeMap(t_list *head, int size, settings *settings)
{
	char *tmpVis;
	char *vis;
	int i;
	t_list *tmp;
	char **map;

	// tmp = head;
	// vis = tmp->content;

	// while(tmp)
	// {
	// 	tmp = tmp->next;
	// 	printf("%s\n", (char *)tmp->content);
	// }
	tmp = skipEmptyLine(head, &i);
	// while(tmp != NULL)
	// {
	// 	// i++;
	// 	// tmp = tmp->next;
	// 	// vis = tmp->content;
	// 	vis = tmp->content;
	// 	if(lineEmptyOrNot(vis) == 1)
	// 	{
	// 		i++;
	// 		tmp = tmp->next;
	// 	}
	// 	else 
	// 		break;
	// }
	settings->mapH = size - i;
	map = mallocMap(size - i);
	// map = (char **)malloc(sizeof(char *) * (size - i));
	// if(map == NULL)
	// {
	// 	printf("Error\nMalloc map error\n");
	// 	exit(-1);
	// }
	// map[0] = "\0";
	i = -1;
	while(tmp)
	{
		vis = tmp->content;
		if(lineEmptyOrNot(vis) == 0)
		{
			tmpVis = vis;
			vis = ft_strdup(tmpVis);
			map[++i] = vis;
		}
		else
		{
			printf("Error\nBad map\n");
			while(i > 0)
				free(map[i--]);
			free(map);
			exit(-1);
		}
		tmp = tmp->next;
	}
	if (map[0][0] == '\0')
	{
		printf("Error\nNo map\n");
		free(map);
		exit(-1);
	}
	return(map);
}