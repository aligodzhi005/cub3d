/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:00:39 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:01:32 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n1;

	n1 = malloc(sizeof(t_list));
	if (!(n1))
		return (NULL);
	n1->content = content;
	n1->next = NULL;
	return (n1);
}
