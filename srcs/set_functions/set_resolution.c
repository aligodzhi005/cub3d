/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:59:59 by rvena             #+#    #+#             */
/*   Updated: 2021/04/24 23:27:27 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	line_correction(const char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)line;
	if (!line)
		return (0);
	while (tmp[i] != '\0')
	{
		if (checkWhtSpc(tmp[i]) == 1)
			tmp[i] = ' ';
		i++;
	}
	return (i);
}

static char	**ft_free_res(char **res)
{
	int	k;

	k = 0;
	while (res[k] != NULL)
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

int	set_resolution(const char *line, t_settings *t_settings)
{
	char	**res;

	line_correction(line);
	if (t_settings->sW != 0 && t_settings->sH != 0)
		return (printRepeatErr());
	res = ft_split(line, ' ');
	if (res[0][1] != '\0' || res[0][0] != 'R')
		return (printBadArg());
	if (checkResNumber(res, 3, 1) == 1)
		return (1);
	t_settings->sW = ft_atoi(res[1]);
	t_settings->sH = ft_atoi(res[2]);
	if (check_resolution_number(res[1], t_settings, 0) == 1
		|| checkResNumber(res, 3, 1) == 1)
		return (1);
	if (check_resolution_number(res[2], t_settings, 1) == 1)
		return (1);
	ft_free_res(res);
	return (0);
}
