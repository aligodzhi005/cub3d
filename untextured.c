/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:16:20 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 23:13:45 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	freeHead(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		free(tmp->content);
	}
}

int	read_file(t_all_data *everything, int *fd)
{
	int		res_check_line;
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	while (get_next_line(*fd, &line))
	{
		res_check_line = check_line((const char *)line, everything->t_settings);
		if (res_check_line == 0)
			ft_lstadd_back(&head, ft_lstnew(line));
		else if (res_check_line == 1)
			return (1);
		else
			free(line);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	everything->map = makeMap(head, ft_lstsize(head), everything->t_settings);
	freeHead(head);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_all_data	ever;

	initEverything1(&ever);
	if (check_read_argv(argc, argv, &fd, &ever.screenshot))
		exit(1);
	if (read_file(&ever, &fd) == 1)
		exit(1);
	if (checkMap(ever.map, ever.t_settings))
		exit(0);
	if (findPlayerSprite(&ever))
		exit(1);
	initEverything2(&ever);
	ever.sprite1 = initSpr(&ever);
	mlx_hook(ever.img->win_ptr, 17, 0, finish_game, &ever);
	mlx_hook(ever.img->win_ptr, 2, 1L << 0, key_hook, ever.player);
	mlx_hook(ever.img->win_ptr, 3, 1L << 0, key_hook_release, ever.player);
	if (ever.screenshot == 1)
	{
		render_next_frame(&ever);
		return (1);
	}
	mlx_loop_hook(ever.img->mlx_ptr, render_next_frame, &ever);
	mlx_loop(ever.img->mlx_ptr);
}
