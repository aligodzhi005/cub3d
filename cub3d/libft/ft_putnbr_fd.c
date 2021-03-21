/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:02:11 by rvena             #+#    #+#             */
/*   Updated: 2020/11/12 17:02:15 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		make_word(char *res, int *num, int len)
{
	int i;

	i = 0;
	while (len > 0)
	{
		res[i] = num[len - 1] + 48;
		i++;
		len--;
	}
}

static int		set_arr(int *num, long temp)
{
	int i;

	i = 0;
	num[i] = temp % 10;
	temp /= 10;
	i++;
	while (temp > 0)
	{
		num[i] = temp % 10;
		i++;
		temp /= 10;
	}
	return (i);
}

void			ft_putnbr_fd(int n, int fd)
{
	int		arr[11];
	long	temp;
	int		len;
	char	res[12];

	temp = n;
	if (n < 0)
		temp *= -1;
	len = set_arr(arr, temp);
	if (n < 0)
	{
		res[0] = '-';
		make_word(&res[1], arr, len);
		write(fd, res, len + 1);
		return ;
	}
	make_word(res, arr, len);
	write(fd, res, len);
	return ;
}
