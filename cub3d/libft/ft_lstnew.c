/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:00:39 by rvena             #+#    #+#             */
/*   Updated: 2020/11/10 16:00:54 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *n1;

	if (!(n1 = malloc(sizeof(t_list))))
		return (NULL);
	n1->content = content;
	n1->next = NULL;
	return (n1);
}
