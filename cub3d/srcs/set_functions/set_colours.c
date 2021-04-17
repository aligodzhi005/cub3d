/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:11:11 by rvena             #+#    #+#             */
/*   Updated: 2021/04/16 16:31:20 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int countNumberOfDigit(int i)
{
	int count;

	count = 0;
	if (i == 0)
		return (1);
	while(i != 0)
	{
		i /= 10;
		count++;
	}
	return(count);
}

static int setColor(const char *line, long *color)
{
	char	*tmp;
	int		num;
	int		i;

	num = 16777216;
	tmp = (char *)line;
	if(*color != -1)
	{
		printf("Error\nRepeatable colour\n");
		// printf("line = %s\n", line);
		exit(0);
	}
	while(*tmp)
	{
		while(checkWhtSpc(*tmp) == 1)
			tmp++;
		num /= 256;
		i = ft_atoi(tmp);
		if(*color == -1)
			*color += 1;
		*color += i * num;
		tmp += countNumberOfDigit(i);
		if(*color < 0 || num < 1 || i > 255)
		{
			printf("Error\nBad color\n");
			return(1);
		}
		while(checkWhtSpc(*tmp) == 1 || *tmp == ',')
			tmp++;
	}
	// free(tmp);
	return(0);
}

int chooseFlOrCl(const char *line, settings *settings)
{
	int i;

	i = 0;
	if (line[i] == 'F' && checkWhtSpc(line[i + 1]) == 1)
		return(setColor(&line[i + 1], &settings->floor));
	else if (line[i] == 'C' && checkWhtSpc(line[i + 1]) == 1)
		return(setColor(&line[i + 1], &settings->ceilling));
	else 
		return(printBadArg());
}