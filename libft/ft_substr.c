/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:20:30 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 13:26:58 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*str;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start >= slen)
	{
		str = (char *)malloc((slen + 1) * sizeof(char));
		str[0] = '\0';
		return (str);
	}
	if (slen < len)
		str = (char *)malloc((slen + 1) * sizeof(char));
	else
		str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i] && i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
