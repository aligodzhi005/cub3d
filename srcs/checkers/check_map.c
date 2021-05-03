/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:41:13 by rvena             #+#    #+#             */
/*   Updated: 2021/04/26 19:45:46 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	mapNormalize(char **map, t_settings *t_settings)
{
	char	*tmp;
	size_t	line_length;
	int		i;

	i = 0;
	while (i < t_settings->mapH)
	{
		line_length = ft_strlen(map[i]);
		if ((int)line_length <= t_settings->mapW)
		{
			tmp = map[i];
			map[i] = (char *)malloc((t_settings->mapW + 1) * sizeof(char));
			if (map[i] == NULL)
				printfMallocMap();
			map[i][t_settings->mapW + 1] = '\0';
			map[i] = ft_memcpy(map[i], tmp, line_length);
			while ((int)line_length < t_settings->mapW + 1)
				map[i][line_length++] = ' ';
			free(tmp);
		}
		i++;
	}
	return (0);
}

static int	checkHorLine(char **map, t_settings *t_settings, int i)
{
	int	start;
	int	j;

	start = 0;
	j = 0;
	while (map[i][j] != '\0')
	{
		if (ft_strchr("012NSWE ", map[i][j]) == NULL)
			return (printBadMap());
		else if (map[i][j] == '1')
			start = 1;
		else if (ft_strchr("02NSWE", map[i][j]) != NULL)
			if (start != 1 || map[i][j + 1] == ' '
				|| map[i][j + 1] == '\0' || map[i][j - 1] == ' ')
				return (printBadMap());
		j++;
	}
	if (j > t_settings->mapW)
		t_settings->mapW = j;
	return (0);
}

static int	checkVerLine(char **map, t_settings *t_settings, int j)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (i < t_settings->mapH)
	{
		if (map[i][j] == '1')
			start = 1;
		else if (ft_strchr("02NSWE", map[i][j]) != NULL)
			if (start != 1 || i == (t_settings->mapH - 1)
				|| map[i - 1][j] == ' '
				|| map[i + 1][j] == ' ')
				return (printBadMap());
		i++;
	}
	return (0);
}

int	checkMap(char **map, t_settings *t_settings)
{
	int	i;
	int	j;

	i = 0;
	while (i < t_settings->mapH)
	{
		j = checkHorLine(map, t_settings, i);
		if (j < 0)
			return (j);
		i++;
	}
	mapNormalize(map, t_settings);
	while (j < t_settings->mapW)
	{
		i = checkVerLine(map, t_settings, j);
		if (i > 0)
			return (i);
		j++;
	}
	return (0);
}
