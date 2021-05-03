/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_read_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:00:17 by rvena             #+#    #+#             */
/*   Updated: 2021/04/22 15:40:07 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_argv_cub(char *argv, int *fd)
{
	char	*tmp;
	int		ret;

	tmp = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (tmp != 0 && *(tmp + 4) == '\0')
	{
		*fd = open(argv, O_RDONLY);
		ret = read(*fd, tmp, 0);
		if (ret == -1)
		{
			printf("Error\n%s is not file\n", argv);
			close(*fd);
			exit(-1);
		}
		return (0);
	}
	printf("Error\nBad map file");
	return (1);
}

int	check_read_argv(int argc, char **argv, int*fd, int *screen)
{
	if (argc == 2)
		return (check_argv_cub(argv[1], fd));
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[1])) == 0
			&& check_argv_cub(argv[1], fd) == 0)
		{
			*screen = 1;
			return (0);
		}
		printf("Error\nBad argument after or before ./cub3d\n");
		exit(-1);
	}
	printf("Error\nToo many arguments after ./cub3d or there is no arguments");
	return (1);
}
