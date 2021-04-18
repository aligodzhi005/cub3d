/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:06:50 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 18:58:23 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_remains(char **remains, char **line)
{
	char	*p_n;
	char	*tmp;

	tmp = NULL;
	p_n = NULL;
	if (!line)
		return (p_n);
	if (*remains)
	{
		p_n = ft_strchr(*remains, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(*remains);
			p_n++;
			ft_strlcpy(*remains, p_n, ft_strlen(p_n) + 1);
		}
		else
			*line = ft_strdup(*remains);
	}
	else
		*line = ft_strdup("");
	return (p_n);
}

int	ft_return(int fd, int ret, char **remains)
{
	if (fd < 0 || ret < 0)
		return (-1);
	if (ret == 0)
	{
		free(*remains);
		*remains = NULL;
		return (0);
	}
	return (1);
}

int	ft_read(int fd, char **line, char **remains, char *p_n)
{
	char	buf[10 + 1];
	char	*tmp;
	int		ret;

	ret = 1;
	while (!p_n)
	{
		ret = read(fd, buf, 10);
		if (ret < 1)
			break ;
		p_n = ft_strchr(buf, '\n');
		if (p_n)
		{
			*p_n = '\0';
			tmp = *remains;
			*remains = ft_strdup(p_n + 1);
			free(tmp);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*remains;
	int			ret;
	char		*p_n;
	char		*tmp;

	tmp = NULL;
	p_n = NULL;
	ret = 1;
	if (!line)
		return (-1);
	p_n = check_remains(&remains, line);
	ret = ft_read(fd, line, &remains, p_n);
	return (ft_return(fd, ret, &remains));
}
