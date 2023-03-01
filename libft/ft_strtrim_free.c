/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:44:54 by vjean             #+#    #+#             */
/*   Updated: 2022/11/14 11:47:10 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim_free(char *s1, char const *set)
{
	int	end;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]) != NULL)
		end--;
	free (s1);
	return (ft_substr(s1, 0, end + 1));
}
