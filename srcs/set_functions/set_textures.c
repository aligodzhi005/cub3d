/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:07:43 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:20:46 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	checkTexPath(char *res)
{
	int		fd;
	int		ret;
	char	temp[1];

	fd = open(res, O_RDONLY);
	ret = read(fd, temp, 0);
	if (ret == -1)
	{
		printf("Error\nBad texture path\n");
		close(fd);
		exit(-1);
	}
	if (!(ft_strnstr(res, ".png", ft_strlen(res))))
	{
		printf("Error\nTexture is not PNG\n");
		exit(-1);
	}
	close(fd);
}

int	setTexPath(const char *line, char **p)
{
	char	*tmp;
	int		len;
	char	*res;

	tmp = (char *)line;
	while (checkWhtSpc(*tmp) == 1)
		tmp++;
	len = ft_strlen(tmp);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
	{
		printf("Error\nMalloc setTexPath error\n");
		exit(-1);
	}
	ft_strlcpy(res, tmp, len + 1);
	checkTexPath(res);
	if (*p == NULL)
		*p = res;
	else
		return (printRepeatErr());
	return (0);
}

int	setTex(const char *line, t_settings *t_settings)
{
	int	i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O'
		&& checkWhtSpc(line[i + 2]) == 1)
		return (setTexPath(&line[i + 2], &t_settings->NO));
	else if (line[i] == 'S' && line[i + 1] == 'O'
		&& checkWhtSpc(line[i + 2]) == 1)
		return (setTexPath(&line[i + 2], &t_settings->SO));
	else if (line[i] == 'W' && line[i + 1] == 'E'
		&& checkWhtSpc(line[i + 2]) == 1)
		return (setTexPath(&line[i + 2], &t_settings->WE));
	else if (line[i] == 'E' && line[i + 1] == 'A'
		&& checkWhtSpc(line[i + 2]) == 1)
		return (setTexPath(&line[i + 2], &t_settings->EA));
	else if (line[i] == 'S' && checkWhtSpc(line[i + 1]) == 1)
		return (setTexPath(&line[i + 2], &t_settings->S));
	printf("Error\nBad type argument\n");
	return (1);
}
