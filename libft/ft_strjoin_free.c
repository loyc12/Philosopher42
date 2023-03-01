/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:54:16 by vjean             #+#    #+#             */
/*   Updated: 2023/01/20 12:26:47 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*nstr;
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	nstr = (char *)malloc((s1len + s2len + 1) * (sizeof(char)));
	if (!nstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		nstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		nstr[j++] = s2[i++];
	nstr[j] = '\0';
	ft_free_null(s1);
	ft_free_null(s2);
	return (nstr);
}
