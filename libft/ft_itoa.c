/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:30:55 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 20:01:17 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_word(char *res, int *num, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		res[i] = num[len - 1] + 48;
		i++;
		len--;
	}
	res[i] = '\0';
}

static int	set_arr(int *num, long temp)
{
	int	i;

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

char	*ft_itoa(unsigned long long n)
{
	int					arr[10];
	unsigned long long	temp;
	int					len;
	char				*res;

	temp = n;
	if (n < 0)
		temp *= -1;
	len = set_arr(arr, temp);
	if (n < 0)
	{
		res = malloc((len + 2) * sizeof(char));
		if (!(res))
			return (NULL);
		*res = '-';
		make_word(++res, arr, len);
		return (--res);
	}
	res = malloc((len + 1) * sizeof(char));
	if (!(res))
		return (NULL);
	make_word(res, arr, len);
	return (res);
}
