/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:49:23 by rvena             #+#    #+#             */
/*   Updated: 2020/11/12 16:07:25 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_inset(char const s1, char const *set)
{
	char	*temp_set;
	int		j;

	temp_set = (char *)set;
	j = 0;
	while (*temp_set != '\0')
	{
		if (*temp_set == s1)
		{
			j = 1;
			break ;
		}
		temp_set++;
	}
	return (j);
}
