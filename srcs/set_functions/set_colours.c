/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:11:11 by rvena             #+#    #+#             */
/*   Updated: 2021/04/25 03:34:09 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	countNumberOfDigit(int i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

static void	setColor2(int *num, long *color, int *i, char **tmp)
{
	*num /= 256;
	*i = ft_atoi(*tmp);
	if (*color == -1)
		*color += 1;
	*color += *i * *num;
	*tmp += countNumberOfDigit(*i);
}

static int	setColor3(int count)
{
	if (count != 3)
	{
		printf("Error\nBad number of colors\n");
		exit(-1);
	}
	return (0);
}

static char	*skipSpComma(char *tmp)
{
	int	count;

	count = 0;
	while (checkWhtSpc(*tmp) == 1 || *tmp == ',')
	{
		if (*tmp == ',')
		{
			if (count == 0)
				count = 1;
			else
			{
				printf("Error\nToo many comma\n");
				exit(-1);
			}
		}
		tmp++;
	}
	if (count == 0 && *tmp != '\0')
	{
		printf("Error\nNo comma between colors\n");
		exit(-1);
	}
	return (tmp);
}

int	setColor(const char *line, long *color)
{
	char	*tmp;
	int		num;
	int		i;
	int		count;

	count = 0;
	num = 16777216;
	tmp = (char *)line;
	if (*color != -1)
		printfRepeatableColor();
	countComma(tmp);
	while (*tmp)
	{
		while (checkWhtSpc(*tmp) == 1)
			tmp++;
		setColor2(&num, color, &i, &tmp);
		count++;
		if (*color < 0 || num < 1 || i > 255 || i < 0)
		{
			printf("Error\nBad color\n");
			return (1);
		}
		tmp = skipSpComma(tmp);
	}
	return (setColor3(count));
}
