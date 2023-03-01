/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42quebec.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:13:51 by vjean             #+#    #+#             */
/*   Updated: 2022/05/09 13:00:00 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_longint(int nb)
{
	int	i;

	if (nb == 0)
		return (1);
	i = 0;
	if (nb < 0)
		i++;
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*temp;
	int		sign;

	i = ft_longint(n) - 1;
	temp = ft_calloc(ft_longint(n) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	if (n == -2147483648)
		return (ft_memcpy(temp, "-2147483648", 11));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	while (i >= 0)
	{	
		temp[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	if (sign == 1)
			temp[0] = '-';
	return (temp);
}
